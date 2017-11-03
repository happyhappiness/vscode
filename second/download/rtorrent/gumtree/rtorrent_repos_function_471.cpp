void
DownloadList::pause(Download* download) {
  check_contains(download);

  try {

    // Always clear hashing on pause. When a hashing request is added,
    // it should have cleared the hash resume data.
    if (rpc::call_command_d_value("d.get_hashing", download) != Download::variable_hashing_stopped) {
      download->download()->hash_stop();
      rpc::call_command_d_set_value("d.set_hashing", download, Download::variable_hashing_stopped);

      std::for_each(slot_map_hash_removed().begin(), slot_map_hash_removed().end(), download_list_call(download));
    }

    if (!download->download()->is_active())
      return;

    download->download()->stop();
    torrent::resume_save_progress(*download->download(), download->download()->bencode()->get_key("libtorrent_resume"));
    
    std::for_each(slot_map_stop().begin(), slot_map_stop().end(), download_list_call(download));

    rpc::call_command_d("d.set_state_changed", download, cachedTime.seconds());

    // Save the state after all the slots, etc have been called so we
    // include the modifications they may make.
    //control->core()->download_store()->save(download);

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}