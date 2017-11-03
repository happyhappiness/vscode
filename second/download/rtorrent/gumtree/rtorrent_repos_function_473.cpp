void
DownloadList::hash_done(Download* download) {
  check_contains(download);

  if (download->is_hash_checking() || download->is_active())
    throw torrent::internal_error("DownloadList::hash_done(...) download in invalid state.");

  if (!download->is_hash_checked()) {
    download->set_hash_failed(true);
    
    std::for_each(slot_map_hash_done().begin(), slot_map_hash_done().end(), download_list_call(download));
    return;
  }

  // Need to find some sane conditional here. Can we check the total
  // downloaded to ensure something was transferred, thus we didn't
  // just hash an already completed torrent with lacking session data?
  //
  // Perhaps we should use a seperate variable or state, and check
  // that. Thus we can bork the download if the hash check doesn't
  // confirm all the data, avoiding large BW usage on f.ex. the
  // ReiserFS bug with >4GB files.

  int64_t hashing = rpc::call_command_d_value("d.get_hashing", download);
  rpc::call_command_d_set_value("d.set_hashing", download, Download::variable_hashing_stopped);

  switch (hashing) {
  case Download::variable_hashing_initial:
  case Download::variable_hashing_rehash:
    // Normal re/hashing.

    // If the download was previously completed but the files were
    // f.ex deleted, then we clear the state and complete.
    if (rpc::call_command_d_value("d.get_complete", download) && !download->is_done()) {
      rpc::call_command_d("d.set_state", download, (int64_t)0);
      download->set_message("Download registered as completed, but hash check returned unfinished chunks.");
    }

    // Save resume data so we update time-stamps and priorities if
    // they were invalid/changed while loading/hashing.
    rpc::call_command_d("d.set_complete", download, (int64_t)download->is_done());
    torrent::resume_save_progress(*download->download(), download->download()->bencode()->get_key("libtorrent_resume"));

    if (rpc::call_command_d_value("d.get_state", download) == 1)
      resume(download);

    break;

  case Download::variable_hashing_last:

    if (download->is_done()) {
      confirm_finished(download);
    } else {
      download->set_message("Hash check on download completion found bad chunks, consider using \"safe_sync\".");
      control->core()->push_log("Hash check on download completion found bad chunks, consider using \"safe_sync\".");
    }
    
    break;

  case Download::variable_hashing_stopped:
  default:
    // Either an error or someone wrote to the hashing variable...
    download->set_message("Hash check completed but the \"hashing\" variable is in an invalid state.");
    return;
  }

  std::for_each(slot_map_hash_done().begin(), slot_map_hash_done().end(), download_list_call(download));
}