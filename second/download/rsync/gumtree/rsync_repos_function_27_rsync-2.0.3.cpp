static int is_regex(char *str)
{
  return strchr(str, '*') || strchr(str, '[') || strchr(str, '?');
}