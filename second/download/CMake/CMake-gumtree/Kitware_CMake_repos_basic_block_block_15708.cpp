{
  size_t length_str, length_suffix;

  if ((str == NULL) || (suffix == NULL))
    return -1;

  length_str = strlen(str);
  length_suffix = strlen(suffix);

  if (length_str >= length_suffix) {
    return strcmp(str + (length_str - length_suffix), suffix);
  } else {
    return -1;
  }
}