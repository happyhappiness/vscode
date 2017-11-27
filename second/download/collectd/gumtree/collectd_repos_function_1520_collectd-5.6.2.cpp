static int get_integer_opt(const char *str, int *ret_value) /* {{{ */
{
  char *endptr;
  int tmp;

  errno = 0;
  endptr = NULL;
  tmp = (int)strtol(str, &endptr, /* base = */ 0);
  if (errno != 0) {
    fprintf(stderr, "Unable to parse option as a number: \"%s\": %s\n", str,
            strerror(errno));
    exit(EXIT_FAILURE);
  } else if (endptr == str) {
    fprintf(stderr, "Unable to parse option as a number: \"%s\"\n", str);
    exit(EXIT_FAILURE);
  } else if (*endptr != 0) {
    fprintf(stderr, "Garbage after end of value: \"%s\"\n", str);
    exit(EXIT_FAILURE);
  }

  *ret_value = tmp;
  return (0);
}