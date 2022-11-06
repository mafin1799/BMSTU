package main

import "fmt"

func main() {
	x0 := 0.0
	y0 := 1.0
	x := 2.0
	h := 0.2
	fmt.Println("Введите 1 - Метод Рунге Кутта \n Введите 2 - Метод Эйлера \n Введите 3 - Метод прогонки")
	N := 0
	fmt.Scan(&N)
	if N == 1 {
		rungeKutta(x0, y0, x, h)
	}
	if N == 2 {
		euler(x0, y0, x, h)
	}
	if N == 3 {
		progonka(50)
	}

}
