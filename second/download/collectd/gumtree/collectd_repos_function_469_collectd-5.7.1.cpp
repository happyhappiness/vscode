static int mr_add_regex(mr_regex_t **re_head, const char *re_str, /* {{{ */
                        const char *option) {
  mr_regex_t *re;
  int status;

  re = calloc(1, sizeof(*re));
  if (re == NULL) {
    log_err("mr_add_regex: calloc failed.");
    return (-1);
  }
  re->next = NULL;

  re->re_str = strdup(re_str);
  if (re->re_str == NULL) {
    sfree(re);
    log_err("mr_add_regex: strdup failed.");
    return (-1);
  }

  status = regcomp(&re->re, re->re_str, REG_EXTENDED | REG_NOSUB);
  if (status != 0) {
    char errmsg[1024];
    regerror(status, &re->re, errmsg, sizeof(errmsg));
    errmsg[sizeof(errmsg) - 1] = 0;
    log_err("Compiling regex `%s' for `%s' failed: %s.", re->re_str, option,
            errmsg);
    sfree(re->re_str);
    sfree(re);
    return (-1);
  }

  if (*re_head == NULL) {
    *re_head = re;
  } else {
    mr_regex_t *ptr;

    ptr = *re_head;
    while (ptr->next != NULL)
      ptr = ptr->next;

    ptr->next = re;
  }

  return (0);
}