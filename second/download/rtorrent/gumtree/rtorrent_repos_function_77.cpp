torrent::Object
apply_remove_untied() {
  for (core::DownloadList::iterator itr = control->core()->download_list()->begin(); itr != control->core()->download_list()->end(); ) {
    rak::file_stat fs;
    const std::string& tiedToFile = rpc::call_command_d_string("d.get_tied_to_file", *itr);

    if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile))) {
      // Need to clear tied_to_file so it doesn't try to delete it.
      rpc::call_command_d("d.set_tied_to_file", *itr, std::string());

      itr = control->core()->download_list()->erase(itr);

    } else {
      ++itr;
    }
  }

  return torrent::Object();
}