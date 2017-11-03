void
DownloadList::resume(Download* download) {
  check_contains(download);

  try {

    if (download->download()->is_active())
      return;

    // Manual or end-of-download rehashing clears the resume data so
    // we can just start the hashing again without clearing it again.
    //
    // It is also assumed the is_hash_checked flag gets cleared when
    // 'hashing' was set.
    if (!download->is_hash_checked()) {
      // If the hash failed flag wasn't cleared then hashing won't be
      // initiated.
      if (download->is_hash_failed())
        return;

      if (rpc::call_command_d_value("d.get_hashing", download) == Download::variable_hashing_stopped)
        rpc::call_command_d("d.set_hashing", download, Download::variable_hashing_initial);

      std::for_each(slot_map_hash_queued().begin(), slot_map_hash_queued().end(), download_list_call(download));
      return;
    }

    // This will never actually do anything due to the above hash check.
    // open_throw(download);

    rpc::call_command_d("d.set_state_changed", download, cachedTime.seconds());

    if (download->is_done()) {
      rpc::call_command_d("d.set_connection_current", download, rpc::call_command_d_void("d.get_connection_seed", download));
    } else {
      rpc::call_command_d("d.set_connection_current", download, rpc::call_command_d_void("d.get_connection_leech", download));

      // For the moment, clear the resume data so we force hash-check
      // on non-complete downloads after a crash. This shouldn't be
      // needed, but for some reason linux 2.6 is very lazy about
      // updating mtime.
      torrent::resume_save_progress(*download->download(), download->download()->bencode()->get_key("libtorrent_resume"), true);
    }

    // Update the priority to ensure it has the correct
    // seeding/unfinished modifiers.
    download->set_priority(download->priority());
    download->download()->start();

    std::for_each(slot_map_start().begin(), slot_map_start().end(), download_list_call(download));

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}