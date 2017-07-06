package main

import (
	"log"
	"net"
	"os"
	"fmt"
	"strconv"
	"bytes"
)

func fib_server() {
	log.SetOutput(os.Stdout)
	listener, _ := net.Listen("tcp", ":25000")
	for {
		conn, _ := listener.Accept()
		fmt.Println("Connection: ", conn.RemoteAddr())
		go fib_handler(conn)
	}
}

func fib_handler(conn net.Conn) {
	for {
		buff := make([]byte, 50)
		buff_len, err := conn.Read(buff)
		if err != nil {
			return
		}
		// Trim the extra bytes in the buffer
		buff = bytes.TrimSpace(buff[:buff_len])
		str_n := string(buff)

		// Convert the string repr of n to an int
		n, _ := strconv.Atoi(string(str_n))

		f := fib(n)

		// Convert fib(n) to string
		res := fmt.Sprintf("%v\n", f)

		// Convert res to bytes and send over socket
		conn.Write([]byte(res))
	}
}

func main() {
	fib_server()
}
