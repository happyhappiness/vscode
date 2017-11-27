latency_counter_t *latency_counter_create (void) /* {{{ */
{
  latency_counter_t *lc;

  lc = malloc (sizeof (*lc));
  if (lc == NULL)
    return (NULL);
  memset (lc, 0, sizeof (*lc));

  latency_counter_reset (lc);
  lc->bin_width = HISTOGRAM_DEFAULT_BIN_WIDTH;
  return (lc);
}