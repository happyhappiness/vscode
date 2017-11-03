torrent::Object
apply_tos(const torrent::Object& rawArg) {
  rpc::Command::value_type value;
  torrent::ConnectionManager* cm = torrent::connection_manager();

  const std::string& arg = rawArg.as_string();

  if (arg == "default")
    value = torrent::ConnectionManager::iptos_default;
  else if (arg == "lowdelay")
    value = torrent::ConnectionManager::iptos_lowdelay;
  else if (arg == "throughput")
    value = torrent::ConnectionManager::iptos_throughput;
  else if (arg == "reliability")
    value = torrent::ConnectionManager::iptos_reliability;
  else if (arg == "mincost")
    value = torrent::ConnectionManager::iptos_mincost;
  else if (!rpc::parse_whole_value_nothrow(arg.c_str(), &value, 16, 1))
    throw torrent::input_error("Invalid TOS identifier.");

  cm->set_priority(value);

  return torrent::Object();
}