char *subst_string(char *buf, size_t buflen, const char *string,
                   const char *needle, const char *replacement) {
  size_t needle_len;
  size_t i;

  if ((buf == NULL) || (string == NULL) || (needle == NULL) ||
      (replacement == NULL))
    return NULL;

  needle_len = strlen(needle);
  sstrncpy(buf, string, buflen);

  /* Limit the loop to prevent endless loops. */
  for (i = 0; i < buflen; i++) {
    char temp[buflen];
    char *begin_ptr;
    size_t begin;

    /* Find `needle' in `buf'. */
    begin_ptr = strstr(buf, needle);
    if (begin_ptr == NULL)
      break;

    /* Calculate the start offset. */
    begin = begin_ptr - buf;

    /* Substitute the region using `subst'. The result is stored in
     * `temp'. */
    begin_ptr =
        subst(temp, buflen, buf, begin, begin + needle_len, replacement);
    if (begin_ptr == NULL) {
      WARNING("subst_string: subst failed.");
      break;
    }

    /* Copy the new string in `temp' to `buf' for the next round. */
    strncpy(buf, temp, buflen);
  }

  if (i >= buflen) {
    WARNING("subst_string: Loop exited after %zu iterations: "
            "string = %s; needle = %s; replacement = %s;",
            i, string, needle, replacement);
  }

  return buf;
}