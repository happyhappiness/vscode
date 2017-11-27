int strtoderive(const char *string, derive_t *ret_value) /* {{{ */
{
  derive_t tmp;
  char *endptr;

  if ((string == NULL) || (ret_value == NULL))
    return (EINVAL);

  errno = 0;
  endptr = NULL;
  tmp = (derive_t)strtoll(string, &endptr, /* base = */ 0);
  if ((endptr == string) || (errno != 0))
    return (-1);

  *ret_value = tmp;
  return (0);
}