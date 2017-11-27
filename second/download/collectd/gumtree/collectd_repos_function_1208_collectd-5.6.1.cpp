void latency_counter_add (latency_counter_t *lc, cdtime_t latency) /* {{{ */
{
  cdtime_t bin;

  if ((lc == NULL) || (latency == 0) || (latency > ((cdtime_t) LLONG_MAX)))
    return;

  lc->sum += latency;
  lc->num++;

  if ((lc->min == 0) && (lc->max == 0))
    lc->min = lc->max = latency;
  if (lc->min > latency)
    lc->min = latency;
  if (lc->max < latency)
    lc->max = latency;

  /* A latency of _exactly_ 1.0 ms should be stored in the buffer 0, so
   * subtract one from the cdtime_t value so that exactly 1.0 ms get sorted
   * accordingly. */
  bin = (latency - 1) / lc->bin_width;
  if (bin >= HISTOGRAM_NUM_BINS)
  {
      change_bin_width (lc, latency);
      bin = (latency - 1) / lc->bin_width;
      if (bin >= HISTOGRAM_NUM_BINS)
      {
          ERROR ("utils_latency: latency_counter_add: Invalid bin: %"PRIu64, bin);
          return;
      }
  }
  lc->histogram[bin]++;
}