void latency_counter_reset (latency_counter_t *lc) /* {{{ */
{
  if (lc == NULL)
    return;

  cdtime_t bin_width = lc->bin_width;
  memset (lc, 0, sizeof (*lc));

  /* preserve bin width */
  lc->bin_width = bin_width;
  lc->start_time = cdtime ();
}