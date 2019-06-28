package main

import (
	"fmt"
)

func rotate(nums []int, k int) {
	arrayLen := len(nums)
	if k > arrayLen {
		k = k % arrayLen
	}
	if k == arrayLen {
		return
	}
	tmparray := make([]int, k)
	//operated_number:=0
	for i := 0; i < arrayLen; i++ {
		if i < k {
			tmparray[k-i-1] = nums[arrayLen-i-1]
		} else {
			nums[arrayLen-i+k-1] = nums[arrayLen-i-1]
		}
	}
	for i := 0; i < k; i++ {
		nums[i] = tmparray[i]
	}
	return
}

func main() {
	inputarray := []int{-1, -100, 3, 99}
	for i := 0; i < len(inputarray)+4; i++ {
		rotate(inputarray, i)
		fmt.Println(i, inputarray)
	}
}