latency_counter_t *latency_counter_create(void) /* {{{ */
{
  latency_counter_t *lc;

  lc = calloc(1, sizeof(*lc));
  if (lc == NULL)
    return (NULL);

  lc->bin_width = HISTOGRAM_DEFAULT_BIN_WIDTH;
  latency_counter_reset(lc);
  return (lc);
}