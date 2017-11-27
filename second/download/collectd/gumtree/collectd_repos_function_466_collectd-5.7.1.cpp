static void mr_free_regex(mr_regex_t *r) /* {{{ */
{
  if (r == NULL)
    return;

  regfree(&r->re);
  memset(&r->re, 0, sizeof(r->re));
  sfree(r->re_str);

  if (r->next != NULL)
    mr_free_regex(r->next);
}