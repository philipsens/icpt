package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"os/exec"
	"strconv"
	"strings"
	"time"
	"unicode"
)

var input []byte

func handleResponse(connection net.Conn) {
	message, _ := bufio.NewReader(connection).ReadString('\n')
	fmt.Printf("\r                                                        \r")
	fmt.Print(message)
	fmt.Print(">> " + string(input))
	return
}

func client(remoteAddress string) {
	fmt.Println("Connecting to", remoteAddress)

	connection, err := net.Dial("tcp", remoteAddress)
	if err != nil {
		fmt.Println("Can't connect to ", remoteAddress)
		return
	}

	for {
		reader := bufio.NewReader(os.Stdin)
		fmt.Print(">> ")
		exec.Command("stty", "-F", "/dev/tty", "cbreak", "min", "1").Run()

		for {
			b, _ := reader.ReadByte()
			if err != nil {
				panic(err)
			}
			if b == '\n' {
				break
			}
			input = append(input, b)
		}
		_, err := fmt.Fprintf(connection, string(input)+"\n")
		if err != nil {
			return
		}
		input = input[:0]
		go handleResponse(connection)
		if strings.TrimSpace(string(input)) == "STOP" {
			fmt.Println("TCP client exiting...")
			return
		}
	}
}

func handleServerResponse(trimmedString string, connection net.Conn) {
	fmt.Printf("\r                                                        \r")
	fmt.Println("client send: " + trimmedString)
	fmt.Print(">> " + string(input))

	if unicode.ToLower(rune(trimmedString[0])) == 's' {
		trimmedString = trimmedString[1:]
	}

	sum := 0
	for _, character := range trimmedString {
		sum += int(character - '0')
	}

	time.Sleep(5 * time.Second)

	connection.Write([]byte("sum: " + strconv.Itoa(sum) + "\n"))
}

func handleConnection(connection net.Conn) {
	for {
		readString, error := bufio.NewReader(connection).ReadString('\n')
		if error != nil {
			fmt.Println(error)
			return
		}

		trimmedString := strings.TrimSpace(string(readString))
		if trimmedString == "STOP" {
			break
		}
		go handleServerResponse(trimmedString, connection)

	}
	connection.Close()
}

func startServer(listener net.Listener) {
	for {
		connection, error := listener.Accept()
		if error != nil {
			fmt.Println(error)
			return
		}
		go handleConnection(connection)
	}
}

func main() {
	arguments := os.Args
	if len(arguments) < 3 {
		fmt.Println("Please provide an address and port!")
		return
	}

	if arguments[1] == "127.0.0.1" {
		listener, error := net.Listen("tcp4", ":"+arguments[2])
		if error != nil {
			errorString := error.Error()
			if strings.Index(errorString, "address already in use") > 0 {
				fmt.Println("Server is already running, starting client.")
			} else {
				fmt.Println(error)
				return
			}
		} else {
			defer listener.Close()

			go startServer(listener)
		}
	}

	client(arguments[1] + ":" + arguments[2])
}
