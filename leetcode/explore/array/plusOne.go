package array

func PlusOne(digits []int) []int {
	arrayLen := len(digits)
	need_forward := true
	for i := arrayLen - 1; i >= 0; i-- {
		digits[i] = (digits[i] + 1) % 10
		if digits[i] > 0 {
			need_forward = false
			break
		}
	}
	if !need_forward {
		return digits
	} else {
		result := make([]int, arrayLen+1)
		result[0] = 1
		return result
	}
}
