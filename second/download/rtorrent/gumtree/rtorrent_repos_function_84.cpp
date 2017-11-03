torrent::Object
apply_call_download(const torrent::Object& rawArgs) {
  const torrent::Object::list_type&          args = rawArgs.as_list();

  if (args.empty())
    throw torrent::input_error("Too few arguments.");

//   const torrent::Object::string_type& infoHash = args.begin()->as_string();

//   core::DownloadList*          dList = control->core()->download_list();
//   core::DownloadList::iterator dItr  = dList->end();

//   if (infoHash.size() == 40)
//     dItr = dList->find_hex(infoHash.c_str());

//   if (dItr == dList->end())
//     throw torrent::input_error("Not a valid info-hash.");

  core::ViewManager* viewManager = control->view_manager();
  core::ViewManager::iterator viewItr;

  if (!args.front().as_string().empty())
    viewItr = viewManager->find(args.front().as_string());
  else
    viewItr = viewManager->find("default");

  if (viewItr == viewManager->end())
    throw torrent::input_error("Could not find view.");

  // Add some pre-parsing of the commands, so we don't spend time
  // parsing and searching command map for every single call.
  torrent::Object             resultRaw(torrent::Object::TYPE_LIST);
  torrent::Object::list_type& result = resultRaw.as_list();

  for (core::View::const_iterator vItr = (*viewItr)->begin_visible(), vLast = (*viewItr)->end_visible(); vItr != vLast; vItr++) {
    torrent::Object::list_type& row = result.insert(result.end(), torrent::Object(torrent::Object::TYPE_LIST))->as_list();

    for (torrent::Object::list_type::const_iterator cItr = ++args.begin(), cLast = args.end(); cItr != args.end(); cItr++) {
      const std::string& cmd = cItr->as_string();
      row.push_back(rpc::parse_command_d_single(*vItr, cmd.c_str(), cmd.c_str() + cmd.size()));
    }
  }

  return resultRaw;
}