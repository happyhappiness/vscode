static int cmc_init(void) /* {{{ */
{
  if (pages_g == NULL) {
    INFO("memcachec plugin: No pages have been defined.");
    return (-1);
  }
  return (0);
}