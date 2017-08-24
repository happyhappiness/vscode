{
  if (!str1 || !str2) {
    return false;
  }
  size_t len1 = strlen(str1), len2 = strlen(str2);
  return len1 >= len2 && !strncmp(str1, str2, len2) ? true : false;
}