cdtime_t latency_counter_get_percentile(latency_counter_t *lc, /* {{{ */
                                        double percent) {
  double percent_upper;
  double percent_lower;
  double p;
  cdtime_t latency_lower;
  cdtime_t latency_interpolated;
  int sum;
  size_t i;

  if ((lc == NULL) || (lc->num == 0) || !((percent > 0.0) && (percent < 100.0)))
    return 0;

  /* Find index i so that at least "percent" events are within i+1 ms. */
  percent_upper = 0.0;
  percent_lower = 0.0;
  sum = 0;
  for (i = 0; i < HISTOGRAM_NUM_BINS; i++) {
    percent_lower = percent_upper;
    sum += lc->histogram[i];
    if (sum == 0)
      percent_upper = 0.0;
    else
      percent_upper = 100.0 * ((double)sum) / ((double)lc->num);

    if (percent_upper >= percent)
      break;
  }

  if (i >= HISTOGRAM_NUM_BINS)
    return 0;

  assert(percent_upper >= percent);
  assert(percent_lower < percent);

  if (i == 0)
    return lc->bin_width;

  latency_lower = ((cdtime_t)i) * lc->bin_width;
  p = (percent - percent_lower) / (percent_upper - percent_lower);

  latency_interpolated =
      latency_lower + DOUBLE_TO_CDTIME_T(p * CDTIME_T_TO_DOUBLE(lc->bin_width));

  DEBUG("latency_counter_get_percentile: latency_interpolated = %.3f",
        CDTIME_T_TO_DOUBLE(latency_interpolated));
  return latency_interpolated;
}