{
  if (!str2) {
    return false;
  }
  size_t len1 = str1.size(), len2 = strlen(str2);
  return len1 >= len2 && !strncmp(str1.c_str() + (len1 - len2), str2, len2)
    ? true
    : false;
}