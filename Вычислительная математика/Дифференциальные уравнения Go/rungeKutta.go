package main

func dydx(x, y float64) float64 {
	return (x - y) / 2
}

func rungeKutta(x0, y0, x, h float64) {
	n := int((x - x0) / h)
	y := y0
	s := "Метод Рунге Кутта (x - y) / 2"
	xs := []float64{}
	ys := []float64{}
	for i := 1; i < n+1; i++ {
		k1 := h * dydx(x0, y)
		k2 := h * dydx(x0+0.5*h, y+0.5*k1)
		k3 := h * dydx(x0+0.5*h, y+0.5*k2)
		k4 := h * dydx(x0+h, y+k3)
		y = y + (1.0/6.0)*(k1+2*k2+2*k3+k4)
		x0 = x0 + h

		xs = append(xs, x0)
		ys = append(ys, y)
	}
	createLineChart(xs, ys, s)

}
