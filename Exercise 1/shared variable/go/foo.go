// Use `go run foo.go` to run your program

package main

import (
	"fmt"
	"runtime"
)

type operation int

const (
	increment operation = iota
	decrement
	read
)

// request represents a request to the server.
type request struct {
	op    operation // operation type
	value chan int  // channel to send value for read operation
}

var (
	serverChan = make(chan request) // Channel for communicating with the server
	workerDone = make(chan bool)
)

// var i = 0

func server() {
	var i int // The server's private variable
	for req := range serverChan {
		switch req.op {
		case increment:
			i++
		case decrement:
			i--
		case read:
			req.value <- i // Send the current value of i back to the requester
		}
	}
}

func incrementing() {
	for j := 0; j < 1000000; j++ {
		serverChan <- request{op: increment}
	}

	workerDone <- true
}

func decrementing() {
	for j := 0; j < 1000000; j++ {
		serverChan <- request{op: decrement}
	}

	workerDone <- true
}

func main() {
	// What does GOMAXPROCS do? What happens if you set it to 1?
	runtime.GOMAXPROCS(2) // GOMAXPROC sets the maximum number of threads than can run simultaniously.

	// TODO: Spawn both functions as goroutines

	go server()

	go incrementing()
	go decrementing()

	<-workerDone
	<-workerDone

	// Request the final value of i from the server
	responseChan := make(chan int)
	serverChan <- request{op: read, value: responseChan}
	i := <-responseChan // Receive the response

	fmt.Println("The magic number is:", i)
	close(serverChan) // Close the server channel
}
