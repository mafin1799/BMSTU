package main

import (
	"bufio"
	"fmt"
	"math"
)

type LinearEquation struct {
	ratio []float64
	value float64
}

type LinearEquationList []LinearEquation

func (list LinearEquationList) getCount() int {
	return len(list)
}

// clone
// клонирует объект
func (list LinearEquationList) clone() LinearEquationList {
	equalCount := list.getCount()
	clone := make(LinearEquationList, equalCount)

	for i := 0; i < equalCount; i++ {
		clone[i].ratio = make([]float64, len(list[i].ratio))
		copy(clone[i].ratio, list[i].ratio)
		clone[i].value = list[i].value
	}
	return clone
}

// print
// печать
func (list LinearEquationList) print(writer *bufio.Writer) error {
	size := list.getCount()

	for i := 0; i < size; i++ {
		for j := 0; j < size; j++ {
			_, err := writer.WriteString(fmt.Sprintf("%.2f*x%d", list[i].ratio[j], j+1))
			if err != nil {
				return err
			}
			if j < size-1 {
				_, err = writer.WriteString(" + ")
				if err != nil {
					return err
				}
			}
		}
		_, err := writer.WriteString(fmt.Sprintf(" = %.2f\n", list[i].value))
		if err != nil {
			return err
		}
	}

	return nil
}

func (system LinearEquationList) normal() LinearEquationList {
	//Диагональное преобладание получаем до преобразования в обьект
	var max float64
	var index int
	var tmp float64
	var handledEquationsCount = 0
	var eps = 0.00001
	var equationsCount = system.getCount()

	for handledEquationsCount < equationsCount {
		// Поиск строки с максимальным a[i][k]
		max = math.Abs(system[handledEquationsCount].ratio[handledEquationsCount])
		index = handledEquationsCount

		for i := handledEquationsCount + 1; i < equationsCount; i++ {
			if tmp := math.Abs(system[i].ratio[handledEquationsCount]); tmp > max {
				max = tmp
				index = i
			}
		}

		// Перестановка строк
		if max < eps {
			// нет ненулевых диагональных элементов
			fmt.Errorf("решение получить невозможно из-за нулевого столбца %d матрицы A", index)
			break
		}

		for j := 0; j < equationsCount; j++ {
			system[handledEquationsCount].ratio[j], system[index].ratio[j] = system[index].ratio[j],
				system[handledEquationsCount].ratio[j]
		}
		system[handledEquationsCount].value, system[index].value = system[index].value,
			system[handledEquationsCount].value

		for i := handledEquationsCount; i < equationsCount; i++ {
			tmp = system[i].ratio[handledEquationsCount]

			// для нулевого коэффициента пропустить
			if math.Abs(tmp) < eps {
				continue
			}

			for j := 0; j < equationsCount; j++ {
				system[i].ratio[j] = system[i].ratio[j] / tmp
			}

			system[i].value = system[i].value / tmp

			// уравнение не вычитать само из себя
			if i == handledEquationsCount {
				continue
			}

			for j := 0; j < equationsCount; j++ {
				system[i].ratio[j] = system[i].ratio[j] - system[handledEquationsCount].ratio[j]
			}
			system[i].value = system[i].value - system[handledEquationsCount].value
		}
		handledEquationsCount++
	}
	return system
}
