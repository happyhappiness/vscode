uint32_t
CommandScheduler::parse_absolute(const char* str) {
  Time result = parse_time(str);
  time_t t;

  // Do the local time thing.
  struct tm local;

  switch (result.first) {
  case 1:
    return result.second;

  case 2:
    t = cachedTime.tval().tv_sec;

    if (localtime_r(&t, &local) == NULL)
      throw torrent::input_error("Could not convert unix time to local time.");

    return (result.second + 3600 - 60 * local.tm_min - local.tm_sec) % 3600;

  case 3:
    t = cachedTime.tval().tv_sec;

    if (localtime_r(&t, &local) == NULL)
      throw torrent::input_error("Could not convert unix time to local time.");

    return (result.second + 24 * 3600 - 3600 * local.tm_hour - 60 * local.tm_min - local.tm_sec) % (24 * 3600);

  case 0:
  default:
    throw torrent::input_error("Could not parse interval.");
  }
}