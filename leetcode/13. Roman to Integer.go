package main

import "fmt"

func main() {
	fmt.Println(romanToInt("D"))
}

func romanToInt(s string) int {
	rome := map[string]int{
		"I": 1,
		"V": 5,
		"X": 10,
		"L": 50,
		"C": 100,
		"D": 500,
		"M": 1000,
	}

	var num, i, c int
	if len(s) == 1 {
		num = rome[s]
		return num
	}
	for {

		if i+1 < len(s) && rome[string(s[i])] >= rome[string(s[i+1])] {
			num = num + rome[string(s[i])]
			c = 100
		}
		if i+1 < len(s) && rome[string(s[i])] < rome[string(s[i+1])] {
			num = num - rome[string(s[i])]
			c = 500
		}

		i++
		if i == len(s) && c == 100 {
			num += rome[string(s[len(s)-1])]
			break
		}
		if i == len(s) && c == 500 {
			num += rome[string(s[len(s)-1])]
			break
		}

	}
	return num
}
