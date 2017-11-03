torrent::Object
apply_stop_untied() {
  for (core::DownloadList::iterator itr = control->core()->download_list()->begin(); itr != control->core()->download_list()->end(); ++itr) {
    if (rpc::call_command_d_value("d.get_state", *itr) == 0)
      continue;

    rak::file_stat fs;
    const std::string& tiedToFile = rpc::call_command_d_string("d.get_tied_to_file", *itr);

    if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile)))
      control->core()->download_list()->stop_try(*itr);
  }

  return torrent::Object();
}