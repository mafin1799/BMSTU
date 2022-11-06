package main

func progonka(n int) {
	h := 0.1
	y1 := 0.77
	y15 := 0.49281
	q := 1.0
	s := "Метод Прогонки Y” +Y’/X+Y=0"
	var p []float64
	var x []float64
	var a []float64
	var b []float64
	var c []float64
	var v []float64
	var u []float64
	u = append(u, y1)
	v = append(v, 0)

	for i := 0; i < n; i++ {
		x = append(x, 1+h*float64(i))
		p = append(p, 1/(x[i]))
		a = append(a, 1-h*p[i]/2)
		b = append(b, h*h*q-2)
		c = append(c, 1+h*p[i]/2)
		u[0] = y1
		if i > 0 {
			v = append(v, -c[i]/(b[i]+a[i]*v[i-1]))

		}
	}
	v = append(v, 0)
	for i := 1; i < n; i++ {
		u = append(u, -a[i]*u[i-1]/(b[i]+a[i]*v[i-1]))
	}
	u = append(u, y15)

	y := make([]float64, n+1)
	y[0] = y1
	y[n] = y15

	for i := n - 1; i > 0; i-- {
		{
			y[i] = u[i] + v[i]*y[i+1]
		}

	}

	createLineChart(x, y, s)
}
