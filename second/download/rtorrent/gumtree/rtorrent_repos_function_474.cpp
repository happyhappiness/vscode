void
DownloadList::hash_queue(Download* download, int type) {
  check_contains(download);

  if (rpc::call_command_d_value("d.get_hashing", download) != Download::variable_hashing_stopped)
    throw torrent::internal_error("DownloadList::hash_queue(...) hashing already queued.");

  close_throw(download);
  torrent::resume_clear_progress(*download->download(), download->download()->bencode()->get_key("libtorrent_resume"));

  download->set_hash_failed(false);
  rpc::call_command_d_set_value("d.set_hashing", download, type);

  if (download->is_open())
    throw torrent::internal_error("DownloadList::hash_clear(...) download still open.");

  // If any more stuff is added here, make sure resume etc are still
  // correct.
  std::for_each(slot_map_hash_queued().begin(), slot_map_hash_queued().end(), download_list_call(download));
}