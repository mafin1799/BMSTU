package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

const path = "temp/input5.txt"

func main() {
	var err error

	fmt.Println("\nСЛАУ:") // --------------------------------------------------------
	writer := bufio.NewWriter(os.Stdout)
	err = readfile(path).print(writer)
	if err != nil {
		log.Fatalln(err)
	}
	err = writer.Flush()
	if err != nil {
		return
	}

	fmt.Println("Решение по Гауссу")
	res, err := readfile(path).clone().solveByGauss()
	if err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Printf("Решение %.7f", res)
	}

	fmt.Println("\nРешение методом простых итераций")
	res, err = readfile(path).clone().solveBySimpleIteration()
	if err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Printf("Решение %.7f", res)
	}

	fmt.Println("\nРешение методом Зейделя")
	res, err = readfile(path).clone().solveBySiedel()
	if err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Printf("Решение %.7f", res)
		//runtime.Breakpoint()
	}

}
