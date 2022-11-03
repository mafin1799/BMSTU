package main

import (
	"fmt"
	"strconv"
)

func main() {
	fmt.Println(isPalindrome(100))
}

func isPalindrome(x int) bool {
	var bs1, bs2 []byte
	var flag bool
	c := 0
	bs := []byte(strconv.Itoa(x))
	if len(bs)%2 == 0 {
		bs1 = bs[:len(bs)/2]
		bs2 = bs[len(bs)/2:]
	}
	if len(bs)%2 != 0 {
		bs1 = bs[:len(bs)/2]
		bs2 = bs[1+len(bs)/2:]
	}

	for i := 0; i < len(bs1); i++ {
		if bs1[i] == bs2[len(bs1)-i-1] {
			c++
		}
	}
	if c == len(bs2) {
		flag = true
	} else {
		flag = false
	}
	return flag

}
