torrent::Object
apply_on_state_change(core::DownloadList::slot_map* slotMap, const torrent::Object& rawArgs) {
  const torrent::Object::list_type& args = rawArgs.as_list();

  if (args.size() == 0 || args.size() > 2)
    throw torrent::input_error("Wrong number of arguments.");

  if (args.front().as_string().empty())
    throw torrent::input_error("Empty key.");

  std::string key = "1_state_" + args.front().as_string();

  if (args.size() == 1)
    slotMap->erase(key);
  else
    (*slotMap)[key] = sigc::bind(sigc::ptr_fun(&rpc::parse_command_d_multiple_std), args.back().as_string());

  return torrent::Object();
}