void
DownloadList::close_throw(Download* download) {
  check_contains(download);

  // When pause gets called it will clear the initial hash check state
  // and set hash failed. This should ensure hashing doesn't restart
  // until resume gets called.
  pause(download);

  // Check for is_open after pause due to hashing.
  if (!download->is_open())
    return;

  // Save the torrent on close, this covers shutdown and if a torrent
  // is manually closed which would clear the progress data. For
  // better crash protection, save regulary in addition to this.
  //
  // Used to be in pause, but this was wrong for rehashing etc.
  //
  // Reconsider this save. Should be done explicitly when shutting down.
  //control->core()->download_store()->save(download);

  download->download()->close();

  if (!download->is_hash_failed() && rpc::call_command_d_value("d.get_hashing", download) != Download::variable_hashing_stopped)
    throw torrent::internal_error("DownloadList::close_throw(...) called but we're going into a hashing loop.");

  std::for_each(slot_map_hash_removed().begin(), slot_map_hash_removed().end(), download_list_call(download));
  std::for_each(slot_map_close().begin(), slot_map_close().end(), download_list_call(download));
}