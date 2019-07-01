package main

func containsDuplicate(nums []int) bool {
	int_map := make(map[int]int)
	numsSize := len(nums)
	var ok bool
	for i := 0; i < numsSize; i++ {
		_, ok = int_map[nums[i]]
		if ok {
			return true
		}
		int_map[nums[i]] = 1
	}
	return false
}
