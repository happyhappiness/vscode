uint32_t
CommandScheduler::parse_interval(const char* str) {
  Time result = parse_time(str);

  if (result.first == 0)
    throw torrent::input_error("Could not parse interval.");
  
  return result.second;
}