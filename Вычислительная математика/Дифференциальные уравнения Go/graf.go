package main

import (
	"github.com/go-echarts/go-echarts/v2/charts"
	"github.com/go-echarts/go-echarts/v2/opts"
	"github.com/go-echarts/go-echarts/v2/types"
	"os"
)

func generateLineItems(arr []float64) []opts.LineData {
	items := make([]opts.LineData, 0)
	for i := 0; i < len(arr); i++ {
		items = append(items, opts.LineData{Value: arr[i]})
	}
	return items
}

func createLineChart(x []float64, y []float64, s string) {
	// create a new line instance
	line := charts.NewLine()

	// set some global options like Title/Legend/ToolTip or anything else
	line.SetGlobalOptions(
		charts.WithInitializationOpts(opts.Initialization{
			Theme: types.ThemeInfographic,
		}),
		charts.WithTitleOpts(opts.Title{
			Title:    "Решение Дифференциального уравнения",
			Subtitle: s,
		}),
	)

	// Put data into instance
	line.SetXAxis(generateLineItems(x)).
		AddSeries("Y", generateLineItems(y)).
		SetSeriesOptions(charts.WithLineChartOpts(opts.LineChart{Smooth: false}))
	f, _ := os.Create("line.html")
	_ = line.Render(f)
}
