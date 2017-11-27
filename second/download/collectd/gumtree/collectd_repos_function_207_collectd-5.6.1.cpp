static int count_chars (const char *str, char chr) {
  int count = 0;

  while (*str != '\0') {
    if (*str == chr) {
      count++;
    }
    str++;
  }

  return count;
}