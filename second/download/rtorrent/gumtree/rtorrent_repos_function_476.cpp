void
DownloadList::confirm_finished(Download* download) {
  check_contains(download);

  rpc::call_command_d("d.set_complete", download, (int64_t)1);

  rpc::call_command_d("d.set_connection_current", download, rpc::call_command_d_void("d.get_connection_seed", download));
  download->set_priority(download->priority());

  if (rpc::call_command_d_value("d.get_min_peers", download) == rpc::call_command_value("get_min_peers") && rpc::call_command_value("get_min_peers_seed") >= 0)
    rpc::call_command_d("d.set_min_peers", download, rpc::call_command_void("get_min_peers_seed"));

  if (rpc::call_command_d_value("d.get_max_peers", download) == rpc::call_command_value("get_max_peers") && rpc::call_command_value("get_max_peers_seed") >= 0)
    rpc::call_command_d("d.set_max_peers", download, rpc::call_command_void("get_max_peers_seed"));

  // Do this before the slots are called in case one of them closes
  // the download.
  if (!download->is_active() && rpc::call_command_value("get_session_on_completion") != 0) {
    torrent::resume_save_progress(*download->download(), download->download()->bencode()->get_key("libtorrent_resume"));
    control->core()->download_store()->save(download);
  }

  // Send the completed request before resuming so we don't reset the
  // up/downloaded baseline.
  download->download()->tracker_list().send_completed();

  // Close before calling on_finished to ensure the user can do stuff
  // like change move the downloaded files and change the directory.
  close_throw(download);
  std::for_each(slot_map_finished().begin(), slot_map_finished().end(), download_list_call(download));

  if (!download->is_active() && rpc::call_command_d_value("d.get_state", download) == 1)
    resume(download);
}