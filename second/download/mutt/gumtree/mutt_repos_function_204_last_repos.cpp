int mutt_atol (const char *str, long *dst)
{
  long r;
  long *res = dst ? dst : &r;
  char *e = NULL;

  /* no input: 0 */
  if (!str || !*str)
  {
    *res = 0;
    return 0;
  }

  *res = strtol (str, &e, 10);
  if ((*res == LONG_MAX && errno == ERANGE) ||
      (e && *e != '\0'))
    return -1;
  return 0;
}