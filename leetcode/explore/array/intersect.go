package array

type numbersOfTwoArray struct {
	nums1 int
	nums2 int
}

func Intersect(nums1 []int, nums2 []int) []int {
	number_map := make(map[int]*numbersOfTwoArray)
	nums1_len := len(nums1)
	nums2_len := len(nums2)
	var ok bool
	for i := 0; i < nums1_len; i++ {
		now_number := nums1[i]
		_, ok = number_map[now_number]
		if ok {
			number_map[now_number].nums1 = number_map[now_number].nums1 + 1
		} else {
			number_map[now_number] = &numbersOfTwoArray{1, 0}
		}
	}

	for i := 0; i < nums2_len; i++ {
		now_number := nums2[i]
		_, ok = number_map[now_number]
		if !ok {
			continue //nums1中不含有该数，直接pass
		} else {
			number_map[now_number].nums2 += 1
		}
	}

	result := make([]int, 0)
	for key, value := range number_map {
		if value.nums2 == 0 {
			continue
		} else {
			if value.nums2 > value.nums1 {
				for i := 0; i < value.nums1; i++ {
					result = append(result, key)
				}
			} else {
				for i := 0; i < value.nums2; i++ {
					result = append(result, key)
				}
			}
		}
	}
	return result
}
