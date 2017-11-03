void
CommandScheduler::parse(const std::string& key, const std::string& bufAbsolute, const std::string& bufInterval, const std::string& command) {
//   char key[21];
//   char bufAbsolute[21];
//   char bufInterval[21];
//   char command[2048];

//   if (std::sscanf(arg.c_str(), "%20[^,],%20[^,],%20[^,],%2047[^\n]", key, bufAbsolute, bufInterval, command) != 4)
//     throw torrent::input_error("Invalid arguments to command.");

  uint32_t absolute = parse_absolute(bufAbsolute.c_str());
  uint32_t interval = parse_interval(bufInterval.c_str());

  CommandSchedulerItem* item = *insert(key);

  item->set_command(command);
  item->set_interval(interval);

  item->enable((cachedTime + rak::timer::from_seconds(absolute)).round_seconds());
}