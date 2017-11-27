static int cc_init (void) /* {{{ */
{
  if (pages_g == NULL)
  {
    INFO ("curl plugin: No pages have been defined.");
    return (-1);
  }
  return (0);
}