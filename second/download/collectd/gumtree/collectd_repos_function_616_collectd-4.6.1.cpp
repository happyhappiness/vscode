static int cc_shutdown (void) /* {{{ */
{
  cc_web_page_free (pages_g);
  pages_g = NULL;

  return (0);
}