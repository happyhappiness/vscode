static int ignorelist_append_regex(ignorelist_t *il, const char *re_str) {
  regex_t *re;
  ignorelist_item_t *entry;
  int status;

  re = calloc(1, sizeof(*re));
  if (re == NULL) {
    ERROR("ignorelist_append_regex: calloc failed.");
    return ENOMEM;
  }

  status = regcomp(re, re_str, REG_EXTENDED);
  if (status != 0) {
    char errbuf[1024];
    (void)regerror(status, re, errbuf, sizeof(errbuf));
    ERROR("utils_ignorelist: regcomp failed: %s", errbuf);
    ERROR("ignorelist_append_regex: Compiling regular expression \"%s\" "
          "failed: %s",
          re_str, errbuf);
    sfree(re);
    return status;
  }

  entry = calloc(1, sizeof(*entry));
  if (entry == NULL) {
    ERROR("ignorelist_append_regex: calloc failed.");
    regfree(re);
    sfree(re);
    return ENOMEM;
  }
  entry->rmatch = re;

  ignorelist_append(il, entry);
  return 0;
}