package main

import "fmt"

func T(str string, char [123]rune) string {
	strToRune := []rune(str)
	for i := 0; i < len(str); i++ {
		if char[(strToRune[i])] != 0 && str[i] >= 'a' && str[i] <= 'z' {
			strToRune[i] = char[strToRune[i]]
		}
		if char[(strToRune[i])] != 0 && str[i] >= 'A' && str[i] <= 'Z' {
			strToRune[i] = char[strToRune[i]+32] - 32
		}
	}
	return string(strToRune)
}

func main() {
	var str [123]rune
	str['b'] = 'z'
	str['c'] = 'x'
	str['d'] = 'w'
	str['f'] = 'v'
	str['g'] = 't'
	str['h'] = 's'
	str['j'] = 'r'
	str['k'] = 'q'
	str['l'] = 'p'
	str['m'] = 'n'

	str['z'] = 'b'
	str['x'] = 'c'
	str['w'] = 'd'
	str['v'] = 'f'
	str['t'] = 'g'
	str['s'] = 'h'
	str['r'] = 'j'
	str['q'] = 'k'
	str['p'] = 'l'
	str['n'] = 'm'

	ss := "hello"

	fmt.Println(T(ss, str))

}
