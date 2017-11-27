static int dns_sleep_one_interval(void) /* {{{ */
{
  struct timespec ts = CDTIME_T_TO_TIMESPEC(plugin_get_interval());
  while (nanosleep(&ts, &ts) != 0) {
    if ((errno == EINTR) || (errno == EAGAIN))
      continue;

    return (errno);
  }

  return (0);
}