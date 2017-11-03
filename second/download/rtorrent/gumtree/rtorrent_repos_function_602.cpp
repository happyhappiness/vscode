char*
TextElementValueBase::print(char* first, char* last, Canvas::attributes_list* attributes, void* object) {
  Attributes baseAttribute = attributes->back();
  push_attribute(attributes, Attributes(first, m_attributes, Attributes::color_invalid));

  int64_t val = value(object);

  // Transform the value if needed.
  if (m_flags & flag_elapsed)
    val = cachedTime.seconds() - val;
  else if (m_flags & flag_remaining)
    val = val - cachedTime.seconds();

  if (m_flags & flag_usec)
    val = rak::timer(val).seconds();

  // Print the value.
  if (first == last) {
    // Do nothing, but ensure that the last attributes are set.

  } else if (m_flags & flag_kb) {
    // Just use a default width of 5 for now.
    first += std::max(snprintf(first, last - first + 1, "%5.1f", (double)val / (1 << 10)), 0);

  } else if (m_flags & flag_mb) {
    // Just use a default width of 8 for now.
    first += std::max(snprintf(first, last - first + 1, "%8.1f", (double)val / (1 << 20)), 0);

  } else if (m_flags & flag_xb) {

    if (val < (int64_t(1000) << 10))
      first += std::max(snprintf(first, last - first + 1, "%5.1f KB", (double)val / (int64_t(1) << 10)), 0);
    else if (val < (int64_t(1000) << 20))
      first += std::max(snprintf(first, last - first + 1, "%5.1f MB", (double)val / (int64_t(1) << 20)), 0);
    else if (val < (int64_t(1000) << 30))
      first += std::max(snprintf(first, last - first + 1, "%5.1f GB", (double)val / (int64_t(1) << 30)), 0);
    else
      first += std::max(snprintf(first, last - first + 1, "%5.1f TB", (double)val / (int64_t(1) << 40)), 0);

  } else if (m_flags & flag_timer) {
    if (val == 0)
      first += std::max(snprintf(first, last - first + 1, "--:--:--"), 0);
    else
      first += std::max(snprintf(first, last - first + 1, "%2d:%02d:%02d", (int)(val / 3600), (int)((val / 60) % 60), (int)(val % 60)), 0);

  } else if (m_flags & flag_date) {
    time_t t = val;
    std::tm *u = std::gmtime(&t);
  
    if (u == NULL)
      return first;

    first += std::max(snprintf(first, last - first + 1, "%02u/%02u/%04u", u->tm_mday, (u->tm_mon + 1), (1900 + u->tm_year)), 0);

  } else if (m_flags & flag_time) {
    time_t t = val;
    std::tm *u = std::gmtime(&t);
  
    if (u == NULL)
      return first;

    first += std::max(snprintf(first, last - first + 1, "%2d:%02d:%02d", u->tm_hour, u->tm_min, u->tm_sec), 0);

  } else {
    first += std::max(snprintf(first, last - first + 1, "%lld", val), 0);
  }

  push_attribute(attributes, Attributes(first, baseAttribute));

  return first;
}