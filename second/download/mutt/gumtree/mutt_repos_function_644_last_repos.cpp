static int string_is_address(const char *str, const char *u, const char *d)
{
  char buf[LONG_STRING];
  
  snprintf(buf, sizeof(buf), "%s@%s", NONULL(u), NONULL(d));
  if (ascii_strcasecmp(str, buf) == 0)
    return 1;
  
  return 0;
}