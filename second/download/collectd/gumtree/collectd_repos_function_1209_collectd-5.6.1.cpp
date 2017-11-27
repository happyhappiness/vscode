void latency_counter_reset (latency_counter_t *lc) /* {{{ */
{
  if (lc == NULL)
    return;

  cdtime_t bin_width = lc->bin_width;
  cdtime_t max_bin = (lc->max - 1) / lc->bin_width;

/*
  If max latency is REDUCE_THRESHOLD times less than histogram's range,
  then cut it in half. REDUCE_THRESHOLD must be >= 2.
  Value of 4 is selected to reduce frequent changes of bin width.
*/
#define REDUCE_THRESHOLD 4
  if ((lc->num > 0) && (lc->bin_width >= HISTOGRAM_DEFAULT_BIN_WIDTH * 2)
     && (max_bin < HISTOGRAM_NUM_BINS / REDUCE_THRESHOLD))
  {
    /* new bin width will be the previous power of 2 */
    bin_width = bin_width / 2;

    DEBUG("utils_latency: latency_counter_reset: max_latency = %.3f; "
          "max_bin = %"PRIu64"; old_bin_width = %.3f; new_bin_width = %.3f;",
        CDTIME_T_TO_DOUBLE (lc->max),
        max_bin,
        CDTIME_T_TO_DOUBLE (lc->bin_width),
        CDTIME_T_TO_DOUBLE (bin_width));
  }

  memset (lc, 0, sizeof (*lc));

  /* preserve bin width */
  lc->bin_width = bin_width;
  lc->start_time = cdtime ();
}