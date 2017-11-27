static void olsrd_set_detail(int *varptr, const char *detail, /* {{{ */
                             const char *key) {
  if (strcasecmp("No", detail) == 0)
    *varptr = OLSRD_WANT_NOT;
  else if (strcasecmp("Summary", detail) == 0)
    *varptr = OLSRD_WANT_SUMMARY;
  else if (strcasecmp("Detail", detail) == 0)
    *varptr = OLSRD_WANT_DETAIL;
  else {
    ERROR("olsrd plugin: Invalid argument given to the `%s' configuration "
          "option: `%s'. Expected: `No', `Summary', or `Detail'.",
          key, detail);
  }
}