static int dns_sleep_one_interval(void) /* {{{ */
{
  cdtime_t interval;
  struct timespec ts = {0, 0};
  int status = 0;

  interval = plugin_get_interval();
  CDTIME_T_TO_TIMESPEC(interval, &ts);

  while (42) {
    struct timespec rem = {0, 0};

    status = nanosleep(&ts, &rem);
    if (status == 0)
      break;
    else if ((errno == EINTR) || (errno == EAGAIN)) {
      ts = rem;
      continue;
    } else
      break;
  }

  return (status);
}