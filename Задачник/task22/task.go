package main

import (
	"errors"
	"fmt"
	"math/big"
)

type para struct {
	Chislo1 int64
	Chislo2 int64
}

func simple(n int64) bool {
	if big.NewInt(n).ProbablyPrime(0) {
		return true
	} else {
		return false
	}
}

func checking(M, N int64) ([]para, error) {
	var Para []para
	var Pair para

	err1 := errors.New("\n<0")
	err2 := errors.New("\nM > N")

	if M < 0 || N < 0 {
		return nil, err1
	}
	if M > N {
		return nil, err2
	}
	for i := M; i <= N; i++ {
		if simple(i) && simple(i+2) {
			Pair.Chislo1 = i
			Pair.Chislo2 = i + 2
			Para = append(Para, Pair)
		}

	}
	return Para, nil
}

func main() {
	fmt.Println(checking(0, 10))
}
