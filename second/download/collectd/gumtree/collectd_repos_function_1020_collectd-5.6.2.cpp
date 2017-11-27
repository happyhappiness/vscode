static int cc_read(void) /* {{{ */
{
  for (web_page_t *wp = pages_g; wp != NULL; wp = wp->next)
    cc_read_page(wp);

  return (0);
}