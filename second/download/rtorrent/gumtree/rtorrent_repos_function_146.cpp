torrent::Object
apply_d_change_link(int changeType, core::Download* download, const torrent::Object& rawArgs) {
  const torrent::Object::list_type& args = rawArgs.as_list();

  if (args.size() != 3)
    throw torrent::input_error("Wrong argument count.");

  torrent::Object::list_type::const_iterator itr = args.begin();

  const std::string& type    = (itr++)->as_string();
  const std::string& prefix  = (itr++)->as_string();
  const std::string& postfix = (itr++)->as_string();
  
  if (type.empty())
    throw torrent::input_error("Invalid arguments.");

  std::string target;
  std::string link;

  if (type == "base_path") {
    target = rpc::call_command_d_string("d.get_base_path", download);
    link = rak::path_expand(prefix + rpc::call_command_d_string("d.get_base_path", download) + postfix);

  } else if (type == "base_filename") {
    target = rpc::call_command_d_string("d.get_base_path", download);
    link = rak::path_expand(prefix + rpc::call_command_d_string("d.get_base_filename", download) + postfix);

  } else if (type == "tied") {
    link = rak::path_expand(rpc::call_command_d_string("d.get_tied_to_file", download));

    if (link.empty())
      return torrent::Object();

    link = rak::path_expand(prefix + link + postfix);
    target = rpc::call_command_d_string("d.get_base_path", download);

  } else {
    throw torrent::input_error("Unknown type argument.");
  }

  switch (changeType) {
  case 0:
    if (symlink(target.c_str(), link.c_str()) == -1)
      //     control->core()->push_log("create_link failed: " + std::string(rak::error_number::current().c_str()));
      //     control->core()->push_log("create_link failed: " + std::string(rak::error_number::current().c_str()) + " to " + target);
      ; // Disabled.
    break;

  case 1:
  {
    rak::file_stat fileStat;
    rak::error_number::clear_global();

    if (!fileStat.update_link(link) || !fileStat.is_link() ||
        unlink(link.c_str()) == -1)
      ; //     control->core()->push_log("delete_link failed: " + std::string(rak::error_number::current().c_str()));

    break;
  }
  default:
    break;
  }

  return torrent::Object();
}