static void change_bin_width (latency_counter_t *lc, cdtime_t latency) /* {{{ */
{
  /* This function is called because the new value is above histogram's range.
   * First find the required bin width:
   *           requiredBinWidth = (value + 1) / numBins
   * then get the next nearest power of 2
   *           newBinWidth = 2^(ceil(log2(requiredBinWidth)))
   */
  double required_bin_width = ((double) (latency + 1)) / ((double) HISTOGRAM_NUM_BINS);
  double required_bin_width_logbase2 = log (required_bin_width) / log (2.0);
  cdtime_t new_bin_width = (cdtime_t) (pow (2.0, ceil (required_bin_width_logbase2)) + .5);
  cdtime_t old_bin_width = lc->bin_width;

  lc->bin_width = new_bin_width;

  /* bin_width has been increased, now iterate through all bins and move the
   * old bin's count to new bin. */
  if (lc->num > 0) // if the histogram has data then iterate else skip
  {
      double width_change_ratio = ((double) old_bin_width) / ((double) new_bin_width);

      for (size_t i = 0; i < HISTOGRAM_NUM_BINS; i++)
      {
         size_t new_bin = (size_t) (((double) i) * width_change_ratio);
         if (i == new_bin)
             continue;
         assert (new_bin < i);

         lc->histogram[new_bin] += lc->histogram[i];
         lc->histogram[i] = 0;
      }
  }

  DEBUG("utils_latency: change_bin_width: latency = %.3f; "
      "old_bin_width = %.3f; new_bin_width = %.3f;",
      CDTIME_T_TO_DOUBLE (latency),
      CDTIME_T_TO_DOUBLE (old_bin_width),
      CDTIME_T_TO_DOUBLE (new_bin_width));
}