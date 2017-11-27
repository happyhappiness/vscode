static _Bool lu_part_matches(part_match_t const *match, /* {{{ */
                             char const *str) {
  if (match->is_regex) {
    /* Short cut popular catch-all regex. */
    if (strcmp(".*", match->str) == 0)
      return 1;

    int status = regexec(&match->regex, str,
                         /* nmatch = */ 0, /* pmatch = */ NULL,
                         /* flags = */ 0);
    if (status == 0)
      return 1;
    else
      return 0;
  } else if (strcmp(match->str, str) == 0)
    return 1;
  else
    return 0;
}