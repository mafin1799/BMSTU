package main

import (
	"fmt"
	"math"
)

func (list LinearEquationList) solveBySimpleIteration() ([]float64, error) {
	var equationsCount = list.getCount()
	var system LinearEquationList = list.normal()
	var res = make([]float64, equationsCount)
	var eps = 0.001
	var xN = make([]float64, equationsCount)
	count := 0

	for i := 0; i < equationsCount; i++ {
		res[i] = system[i].value / system[i].ratio[i]
	}

	for {
		for i := 0; i < equationsCount; i++ {
			xN[i] = system[i].value / system[i].ratio[i]
			for j := 0; j < equationsCount; j++ {
				if i == j {
					continue
				} else {
					xN[i] = xN[i] - (system[i].ratio[j] / system[i].ratio[i] * res[j])
				}
			}
		}
		count++
		if count > 100 {
			break
		}
		fmt.Println("Итерация  №", count, "=", xN)
		flag := true

		for i := 0; i < equationsCount; i++ {
			if math.Abs(xN[i]-res[i]) > eps {
				flag = false
				break
			}

		}
		for i := 0; i < equationsCount; i++ {
			res[i] = xN[i]
		}
		if flag {
			break
		}

	}

	return res, nil
}
