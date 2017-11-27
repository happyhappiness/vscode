static size_t strlisttonums(char *s, uint64_t *nums, size_t max) {
  int ret;
  size_t index = 0;
  char *saveptr = NULL;

  if (s == NULL || nums == NULL || max == 0)
    return index;

  for (;;) {
    char *p = NULL;
    char *token = NULL;

    token = strtok_r(s, ",", &saveptr);
    if (token == NULL)
      break;

    s = NULL;

    while (isspace(*token))
      token++;
    if (*token == '\0')
      continue;

    p = strchr(token, '-');
    if (p != NULL) {
      uint64_t n, start, end;
      *p = '\0';
      ret = strtouint64(token, &start);
      if (ret < 0)
        return 0;
      ret = strtouint64(p + 1, &end);
      if (ret < 0)
        return 0;
      if (start > end) {
        return 0;
      }
      for (n = start; n <= end; n++) {
        if (!(isdup(nums, index, n))) {
          nums[index] = n;
          index++;
        }
        if (index >= max)
          return index;
      }
    } else {
      uint64_t val;

      ret = strtouint64(token, &val);
      if (ret < 0)
        return 0;

      if (!(isdup(nums, index, val))) {
        nums[index] = val;
        index++;
      }
      if (index >= max)
        return index;
    }
  }

  return index;
}