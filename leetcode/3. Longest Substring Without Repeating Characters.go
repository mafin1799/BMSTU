package main

import (
	"fmt"
	"math"
)

func main() {
	fmt.Println(lengthOfLongestSubstring("pwwkew"))
}

func lengthOfLongestSubstring(s string) int {
	var c [128]int

	var left, right, res int

	for right < len(s) {
		r := s[right]
		c[r]++
		for c[r] > 1 {
			l := s[left]
			c[l]--
			left++
		}
		res = int(math.Max(float64(res), float64(right-left+1)))
		right++
	}
	return res
}
