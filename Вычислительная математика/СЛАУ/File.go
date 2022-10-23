package main

import (
	"bufio"
	"log"
	"os"
	"strconv"
	"strings"
)

func readfile(path string) LinearEquationList {
	file, err := os.Open(path)

	if err != nil {
		log.Fatalf("failed to open")

	}
	var matrix [][]float64
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		records := strings.Fields(scanner.Text())
		line := make([]float64, len(records))
		matrix = append(matrix, line)

		for i := range records {
			line[i], err = strconv.ParseFloat(records[i], 64)
			if err != nil {
				panic(err)
			}
		}
	}
	if len(matrix) < len(matrix[0])-1 {
		log.Fatalf("Переменных больше чем уравнений")
	}
	if err = scanner.Err(); err != nil {
		panic(err)
	}
	file.Close()

	var system LinearEquationList
	temp := LinearEquation{
		ratio: nil,
		value: 0,
	}
	for i := 0; i < len(matrix); i++ {
		for j := 0; j < len(matrix[i])-1; j++ {
			temp.ratio = append(temp.ratio, matrix[i][j])
		}
		temp.value = matrix[i][len(matrix[i])-1]
		system = append(system, temp)
		temp.ratio = nil

	}

	//Диагональное преобладание
	return system
}
