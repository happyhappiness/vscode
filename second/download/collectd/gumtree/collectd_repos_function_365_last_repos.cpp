static int mr_match_regexen(mr_regex_t *re_head, /* {{{ */
                            const char *string) {
  if (re_head == NULL)
    return FC_MATCH_MATCHES;

  for (mr_regex_t *re = re_head; re != NULL; re = re->next) {
    int status;

    status = regexec(&re->re, string,
                     /* nmatch = */ 0, /* pmatch = */ NULL,
                     /* eflags = */ 0);
    if (status == 0) {
      DEBUG("regex match: Regular expression `%s' matches `%s'.", re->re_str,
            string);
    } else {
      DEBUG("regex match: Regular expression `%s' does not match `%s'.",
            re->re_str, string);
      return FC_MATCH_NO_MATCH;
    }
  }

  return FC_MATCH_MATCHES;
}