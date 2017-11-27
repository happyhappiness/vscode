static int ps_list_match(const char *name, const char *cmdline,
                         procstat_t *ps) {
#if HAVE_REGEX_H
  if (ps->re != NULL) {
    int status;
    const char *str;

    str = cmdline;
    if ((str == NULL) || (str[0] == 0))
      str = name;

    assert(str != NULL);

    status = regexec(ps->re, str,
                     /* nmatch = */ 0,
                     /* pmatch = */ NULL,
                     /* eflags = */ 0);
    if (status == 0)
      return 1;
  } else
#endif
      if (strcmp(ps->name, name) == 0)
    return 1;

  return 0;
}