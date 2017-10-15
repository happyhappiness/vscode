  return torrent::Object();
}

void apply_import(const std::string& path)     { if (!rpc::parse_command_file(path)) throw torrent::input_error("Could not open option file: " + path); }
void apply_try_import(const std::string& path) { if (!rpc::parse_command_file(path)) control->core()->push_log_std("Could not read resource file: " + path); }

torrent::Object
apply_close_low_diskspace(int64_t arg) {
  core::DownloadList* downloadList = control->core()->download_list();

  bool closed = false;
  core::Manager::DListItr itr = downloadList->begin();

