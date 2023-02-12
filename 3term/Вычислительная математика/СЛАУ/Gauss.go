package main

// solveByGauss
// возвращает список решений СЛАУ по методу Гаусса
func (list LinearEquationList) solveByGauss() ([]float64, error) {
	//var temp float64
	var handledEquationsCount = 0
	//var eps = 0.000001
	var equationsCount = list.getCount()
	var system LinearEquationList = list.normal()

	var x = make([]float64, equationsCount)

	/*for handledEquationsCount < equationsCount {
		// Нормализация уравнений
		for i := handledEquationsCount; i < equationsCount; i++ {
			temp = list[i].ratio[handledEquationsCount]

			// для нулевого коэффициента пропустить
			if math.Abs(temp) < eps {
				continue
			}

			for j := 0; j < equationsCount; j++ {
				list[i].ratio[j] = list[i].ratio[j] / temp
			}

			list[i].value = list[i].value / temp

			// уравнение не вычитать само из себя
			if i == handledEquationsCount {
				continue
			}

			for j := 0; j < equationsCount; j++ {
				list[i].ratio[j] = list[i].ratio[j] - list[handledEquationsCount].ratio[j]
			}
			list[i].value = list[i].value - list[handledEquationsCount].value
		}
		handledEquationsCount++
	}*/

	// обратная подстановка
	for handledEquationsCount = equationsCount - 1; handledEquationsCount >= 0; handledEquationsCount-- {
		x[handledEquationsCount] = system[handledEquationsCount].value
		for i := 0; i < handledEquationsCount; i++ {
			system[i].value = system[i].value - system[i].ratio[handledEquationsCount]*x[handledEquationsCount]
		}
	}

	return x, nil
}
