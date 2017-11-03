CommandScheduler::Time
CommandScheduler::parse_time(const char* str) {
  Time result(0, 0);

  while (true) {
    char* pos;
    result.first++;
    result.second += strtol(str, &pos, 10);

    if (pos == str || result.second < 0)
      return Time(0, 0);

    while (std::isspace(*pos))
      ++pos;

    if (*pos == '\0')
      return result;

    if (*pos != ':' || result.first > 3)
      return Time(0, 0);

    if (result.first < 3)
      result.second *= 60;
    else
      result.second *= 24;

    str = pos + 1;
  }
}