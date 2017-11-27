static int do_loop(void) {
  cdtime_t interval = cf_get_default_interval();
  cdtime_t wait_until;

  wait_until = cdtime() + interval;

  while (loop == 0) {
    cdtime_t now;

#if HAVE_LIBKSTAT
    update_kstat();
#endif

    /* Issue all plugins */
    plugin_read_all();

    now = cdtime();
    if (now >= wait_until) {
      WARNING("Not sleeping because the next interval is "
              "%.3f seconds in the past!",
              CDTIME_T_TO_DOUBLE(now - wait_until));
      wait_until = now + interval;
      continue;
    }

    struct timespec ts_wait = CDTIME_T_TO_TIMESPEC(wait_until - now);
    wait_until = wait_until + interval;

    while ((loop == 0) && (nanosleep(&ts_wait, &ts_wait) != 0)) {
      if (errno != EINTR) {
        char errbuf[1024];
        ERROR("nanosleep failed: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
        return (-1);
      }
    }
  } /* while (loop == 0) */

  return (0);
}