static int cmc_read (void) /* {{{ */
{
  web_page_t *wp;

  for (wp = pages_g; wp != NULL; wp = wp->next)
    cmc_read_page (wp);

  return (0);
}