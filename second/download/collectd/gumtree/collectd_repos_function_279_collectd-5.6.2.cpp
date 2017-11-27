static void time_calc(struct timespec *ts_dest, /* {{{ */
                      const struct timespec *ts_int,
                      const struct timeval *tv_begin,
                      const struct timeval *tv_end) {
  ts_dest->tv_sec = tv_begin->tv_sec + ts_int->tv_sec;
  ts_dest->tv_nsec = (tv_begin->tv_usec * 1000) + ts_int->tv_nsec;
  time_normalize(ts_dest);

  /* Assure that `(begin + interval) > end'.
   * This may seem overly complicated, but `tv_sec' is of type `time_t'
   * which may be `unsigned. *sigh* */
  if ((tv_end->tv_sec > ts_dest->tv_sec) ||
      ((tv_end->tv_sec == ts_dest->tv_sec) &&
       ((tv_end->tv_usec * 1000) > ts_dest->tv_nsec))) {
    ts_dest->tv_sec = tv_end->tv_sec;
    ts_dest->tv_nsec = 1000 * tv_end->tv_usec;
  }

  time_normalize(ts_dest);
}