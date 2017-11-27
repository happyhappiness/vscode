static int cmc_shutdown(void) /* {{{ */
{
  cmc_web_page_free(pages_g);
  pages_g = NULL;

  return (0);
}