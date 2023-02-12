package main

func fun(x, y float64) float64 {
	return (x - y) / 2
}

func euler(x0, y, x, h float64) {
	xs := []float64{}
	ys := []float64{}
	s := "Метод Эйлера (x - y) / 2"
	for x0 < x {
		y = y + h*fun(x0, y)
		x0 = x0 + h
		xs = append(xs, x0)
		ys = append(ys, y)
	}
	createLineChart(xs, ys, s)
}
