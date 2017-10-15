  }

  FREE(&s);
  return rc;
}

static int parse_set (BUFFER *tmp, BUFFER *s, unsigned long data, BUFFER *err)
{
  int query, unset, inv, reset, r = 0;
  int idx = -1;
  const char *p;
  char scratch[_POSIX_PATH_MAX];
