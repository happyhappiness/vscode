{
  if (!str) {
    return 0;
  }
  char* clean_str = new char[strlen(str) + 1];
  char* ptr = clean_str;
  while (*str) {
    if ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')) {
      *ptr++ = *str;
    }
    ++str;
  }
  *ptr = '\0';
  return clean_str;
}