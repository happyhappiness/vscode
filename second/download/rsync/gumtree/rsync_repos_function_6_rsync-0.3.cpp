static int check_one_exclude(char *name,char *pattern)
{
  char *str;

  if (is_regex(pattern)) {
    if (fnmatch(pattern, name, FNM_LEADING_DIR) == 0)
      return 1;
  } else {
    if (str = strstr(name, pattern),
	(str && (str == name || str[-1] == '/')
	 && str[strlen(pattern)] == '\0'))
      return 1;
  }

  return 0;
}