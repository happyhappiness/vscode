static int isdup(const uint64_t *nums, size_t size, uint64_t val) {
  for (size_t i = 0; i < size; i++)
    if (nums[i] == val)
      return 1;
  return 0;
}