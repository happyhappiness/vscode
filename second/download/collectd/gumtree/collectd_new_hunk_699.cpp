  } else if (*endptr != 0) {
    fprintf(stderr, "Garbage after end of value: \"%s\"\n", str);
    exit(EXIT_FAILURE);
  }

  *ret_value = tmp;
  return 0;
} /* }}} int get_integer_opt */

static int get_double_opt(const char *str, double *ret_value) /* {{{ */
{
  char *endptr;
  double tmp;
