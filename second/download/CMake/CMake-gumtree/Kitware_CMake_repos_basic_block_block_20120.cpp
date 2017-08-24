{
  size_t str_len;

  if (str == NULL)
    return -1;

  str_len = wcslen(str);

  /*
    Since we only care about equality, return early if the strings
    aren't the same length
  */
  if (str_len != (file_name_len / sizeof(WCHAR)))
    return -1;

  return _wcsnicmp(str, file_name, str_len);
}