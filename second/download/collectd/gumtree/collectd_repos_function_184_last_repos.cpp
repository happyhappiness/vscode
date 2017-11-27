static int config_set_string(const char *name, /* {{{ */
                             char **var, const char *value) {
  char *tmp;

  tmp = strdup(value);
  if (tmp == NULL) {
    char errbuf[1024];
    ERROR("ping plugin: Setting `%s' to `%s' failed: strdup failed: %s", name,
          value, sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  if (*var != NULL)
    free(*var);
  *var = tmp;
  return 0;
}