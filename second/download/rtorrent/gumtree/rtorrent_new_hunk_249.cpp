void apply_try_import(const std::string& path) { if (!rpc::parse_command_file(path)) control->core()->push_log_std("Could not read resource file: " + path); }

void
apply_close_low_diskspace(int64_t arg) {
  core::DownloadList* downloadList = control->core()->download_list();

  bool closed = false;
  core::Manager::DListItr itr = downloadList->begin();

  while ((itr = std::find_if(itr, downloadList->end(), std::mem_fun(&core::Download::is_downloading)))
         != downloadList->end()) {
    if ((*itr)->file_list()->free_diskspace() < (uint64_t)arg) {
      downloadList->close(*itr);

      (*itr)->set_hash_failed(true);
      (*itr)->set_message(std::string("Low diskspace."));

      closed = true;
    }

    ++itr;
  }

  if (closed)
    control->core()->push_log("Closed torrents due to low diskspace.");    
}

torrent::Object
apply_download_list(const torrent::Object& rawArgs) {
  const torrent::Object::list_type&          args    = rawArgs.as_list();
  torrent::Object::list_type::const_iterator argsItr = args.begin();
