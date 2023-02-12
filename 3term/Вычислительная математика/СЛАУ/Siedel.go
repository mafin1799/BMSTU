package main

import (
	"fmt"
	"math"
)

func (list LinearEquationList) solveBySiedel() ([]float64, error) {
	var equationsCount = list.getCount()
	var previous = make([]float64, equationsCount)
	count := 0
	var system LinearEquationList = list.normal()
	var eps = 0.000001
	for {
		var current = make([]float64, equationsCount)
		for i := 0; i < equationsCount; i++ {
			current[i] = system[i].value
			for j := 0; j < equationsCount; j++ {
				if j < i {
					current[i] = current[i] - (system[i].ratio[j] * current[j])
				}
				if j > i {
					current[i] = current[i] - system[i].ratio[j]*previous[j]
				}
			}
			current[i] = current[i] / system[i].ratio[i]
		}
		var errorr float64 = 0
		for i := 0; i < equationsCount; i++ {
			errorr += math.Abs(current[i] - previous[i])
		}
		if errorr < eps {
			break
		}
		count++
		if count > 100 {
			break
		}
		previous = current
		fmt.Println("Итерация  №", count, "=", previous)
	}

	return previous, nil
}
