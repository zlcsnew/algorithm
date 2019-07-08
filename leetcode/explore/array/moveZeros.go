package array

func MoveZeroes(nums []int) {
	arrayLen := len(nums)
	var now_posi, loop_index int
	for now_posi = 0; now_posi < arrayLen; now_posi++ {
		if nums[now_posi] == 0 {
			break
		}
	}
	for loop_index = now_posi + 1; loop_index < arrayLen; loop_index++ {
		if nums[loop_index] != 0 {
			nums[now_posi] = nums[loop_index]
			nums[loop_index] = 0
			now_posi++
		}
	}
}
