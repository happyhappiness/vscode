double latency_counter_get_rate(const latency_counter_t *lc, /* {{{ */
                                cdtime_t lower, cdtime_t upper,
                                const cdtime_t now) {
  if ((lc == NULL) || (lc->num == 0))
    return NAN;

  if (upper && (upper < lower))
    return NAN;
  if (lower == upper)
    return 0;

  /* Buckets have an exclusive lower bound and an inclusive upper bound. That
   * means that the first bucket, index 0, represents (0-bin_width]. That means
   * that latency==bin_width needs to result in bin=0, that's why we need to
   * subtract one before dividing by bin_width. */
  cdtime_t lower_bin = 0;
  if (lower)
    /* lower is *exclusive* => determine bucket for lower+1 */
    lower_bin = ((lower + 1) - 1) / lc->bin_width;

  /* lower is greater than the longest latency observed => rate is zero. */
  if (lower_bin >= HISTOGRAM_NUM_BINS)
    return 0;

  cdtime_t upper_bin = HISTOGRAM_NUM_BINS - 1;
  if (upper)
    upper_bin = (upper - 1) / lc->bin_width;

  if (upper_bin >= HISTOGRAM_NUM_BINS) {
    upper_bin = HISTOGRAM_NUM_BINS - 1;
    upper = 0;
  }

  double sum = 0;
  for (size_t i = lower_bin; i <= upper_bin; i++)
    sum += lc->histogram[i];

  if (lower) {
    /* Approximate ratio of requests in lower_bin, that fall between
     * lower_bin_boundary and lower. This ratio is then subtracted from sum to
     * increase accuracy. */
    cdtime_t lower_bin_boundary = lower_bin * lc->bin_width;
    assert(lower >= lower_bin_boundary);
    double lower_ratio =
        (double)(lower - lower_bin_boundary) / ((double)lc->bin_width);
    sum -= lower_ratio * lc->histogram[lower_bin];
  }

  if (upper) {
    /* As above: approximate ratio of requests in upper_bin, that fall between
     * upper and upper_bin_boundary. */
    cdtime_t upper_bin_boundary = (upper_bin + 1) * lc->bin_width;
    assert(upper <= upper_bin_boundary);
    double ratio = (double)(upper_bin_boundary - upper) / (double)lc->bin_width;
    sum -= ratio * lc->histogram[upper_bin];
  }

  return sum / (CDTIME_T_TO_DOUBLE(now - lc->start_time));
}