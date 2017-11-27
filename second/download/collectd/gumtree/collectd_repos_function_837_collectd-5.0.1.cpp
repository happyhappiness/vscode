static int cc_read (void) /* {{{ */
{
  web_page_t *wp;

  for (wp = pages_g; wp != NULL; wp = wp->next)
    cc_read_page (wp);

  return (0);
}