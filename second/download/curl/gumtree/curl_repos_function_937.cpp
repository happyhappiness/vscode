long Curl_sleep_time(curl_off_t rate_bps, curl_off_t cur_rate_bps,
                             int pkt_size)
{
  curl_off_t min_sleep = 0;
  curl_off_t rv = 0;

  if(rate_bps == 0)
    return 0;

  /* If running faster than about .1% of the desired speed, slow
   * us down a bit.  Use shift instead of division as the 0.1%
   * cutoff is arbitrary anyway.
   */
  if(cur_rate_bps > (rate_bps + (rate_bps >> 10))) {
    /* running too fast, decrease target rate by 1/64th of rate */
    rate_bps -= rate_bps >> 6;
    min_sleep = 1;
  }
  else if(cur_rate_bps < (rate_bps - (rate_bps >> 10))) {
    /* running too slow, increase target rate by 1/64th of rate */
    rate_bps += rate_bps >> 6;
  }

  /* Determine number of milliseconds to wait until we do
   * the next packet at the adjusted rate.  We should wait
   * longer when using larger packets, for instance.
   */
  rv = ((curl_off_t)((pkt_size * 8) * 1000) / rate_bps);

  /* Catch rounding errors and always slow down at least 1ms if
   * we are running too fast.
   */
  if(rv < min_sleep)
    rv = min_sleep;

  /* Bound value to fit in 'long' on 32-bit platform.  That's
   * plenty long enough anyway!
   */
  if(rv > 0x7fffffff)
    rv = 0x7fffffff;

  return (long)rv;
}