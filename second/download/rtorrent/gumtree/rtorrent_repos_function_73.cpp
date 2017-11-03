torrent::Object
apply_stop_on_ratio(const torrent::Object& rawArgs) {
  const torrent::Object::list_type& args = rawArgs.as_list();

  if (args.empty())
    throw torrent::input_error("Too few arguments.");

  torrent::Object::list_type::const_iterator argItr = args.begin();

  // first argument:  minimum ratio to reach
  // second argument: minimum upload amount to reach [optional]
  // third argument:  maximum ratio to reach [optional]
  int64_t minRatio  = rpc::convert_to_value(*argItr++);
  int64_t minUpload = argItr != args.end() ? rpc::convert_to_value(*argItr++) : 0;
  int64_t maxRatio  = argItr != args.end() ? rpc::convert_to_value(*argItr++) : 0;

  core::DownloadList* downloadList = control->core()->download_list();
  core::Manager::DListItr itr = downloadList->begin();

  while ((itr = std::find_if(itr, downloadList->end(), std::mem_fun(&core::Download::is_seeding)))
         != downloadList->end()) {
    int64_t totalDone   = (*itr)->download()->bytes_done();
    int64_t totalUpload = (*itr)->download()->up_rate()->total();

    if ((totalUpload >= minUpload && totalUpload * 100 >= totalDone * minRatio) ||
        (maxRatio > 0 && totalUpload * 100 > totalDone * maxRatio)) {
      downloadList->stop_try(*itr);
      rpc::call_command_d("d.set_ignore_commands", *itr, (int64_t)1);
    }

    ++itr;
  }

  return torrent::Object();
}