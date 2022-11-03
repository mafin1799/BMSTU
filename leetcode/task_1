func twoSum(nums []int, target int) []int {
	var res []int
	for i := 0; i < len(nums); i++ {
		for j := 0; j < len(nums); j++ {
			if j != i && (nums[i]+nums[j]) == target {
				res = append(res, i)
				res = append(res, j)
				return res
			}
		}

	}
	return res

}
