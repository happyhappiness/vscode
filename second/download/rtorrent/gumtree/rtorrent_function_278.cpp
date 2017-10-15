void
DownloadFactory::receive_success() {
  if (m_stream == NULL)
    throw torrent::internal_error("DownloadFactory::receive_success() called on an object with m_stream == NULL.");

  Download* download = m_manager->download_list()->create(m_stream, m_printLog);

  if (download == NULL) {
    // core::Manager should already have added the error message to
    // the log.
    m_slotFinished();
    return;
  }

  torrent::Object* root = download->bencode();

  if (!m_session) {
    // We only allow session torrents to keep their
    // 'rtorrent/libtorrent' sections. The "fast_resume" section
    // should be safe to keep.
    root->erase_key("rtorrent");
    root->erase_key("libtorrent");
  }

  if (!root->has_key_map("rtorrent"))
    root->insert_key("rtorrent", torrent::Object(torrent::Object::TYPE_MAP));
    
  torrent::Object* rtorrent = &root->get_key("rtorrent");

  initialize_rtorrent(download, rtorrent);

  // Move to 'rtorrent'.
  rpc::call_command_d("set_d_connection_leech", download, m_variables["connection_leech"]);
  rpc::call_command_d("set_d_connection_seed", download,  m_variables["connection_seed"]);

  rpc::call_command_d("set_d_max_uploads", download,      rpc::call_command_void("get_max_uploads"));
  rpc::call_command_d("set_d_min_peers", download,        rpc::call_command_void("get_min_peers"));
  rpc::call_command_d("set_d_max_peers", download,        rpc::call_command_void("get_max_peers"));
  rpc::call_command_d("set_d_tracker_numwant", download,  rpc::call_command_void("get_tracker_numwant"));

  if (rpc::call_command_d_value("get_d_complete", download) != 0) {
    if (rpc::call_command_value("get_min_peers_seed") >= 0)
      rpc::call_command_d("set_d_min_peers", download, rpc::call_command_void("get_min_peers_seed"));

    if (rpc::call_command_value("get_max_peers_seed") >= 0)
      rpc::call_command_d("set_d_max_peers", download, rpc::call_command_void("get_max_peers_seed"));
  }

  if (!rpc::call_command_value("get_use_udp_trackers"))
    download->enable_udp_trackers(false);

  if (rpc::call_command_value("get_max_file_size") > 0)
    rpc::call_command_d("set_d_max_file_size", download, rpc::call_command_void("get_max_file_size"));

  // Check first if we already have these values set in the session
  // torrent, so that it is safe to change the values.
  //
  // Need to also catch the exceptions.
  if (rpc::call_command_value("get_split_file_size") >= 0)
    torrent::file_split_all(download->download()->file_list(),
                            rpc::call_command_value("get_split_file_size"),
                            rpc::call_command_string("split_suffix"));

  if (!rtorrent->has_key_string("directory"))
    rpc::call_command_d("set_d_directory", download, m_variables["directory"]);
  else
    rpc::call_command_d("set_d_directory", download, rtorrent->get_key("directory"));

  if (!m_session && m_variables["tied_to_file"].as_value())
    rpc::call_command_d("set_d_tied_to_file", download, m_uri);

  torrent::Object& resumeObject = root->has_key_map("libtorrent_resume")
    ? root->get_key("libtorrent_resume")
    : root->insert_key("libtorrent_resume", torrent::Object(torrent::Object::TYPE_MAP));

  torrent::resume_load_addresses(*download->download(), resumeObject);
  torrent::resume_load_file_priorities(*download->download(), resumeObject);
  torrent::resume_load_tracker_settings(*download->download(), resumeObject);

  // The action of inserting might cause the torrent to be
  // opened/started or such. Figure out a nicer way of handling this.
  if (m_manager->download_list()->insert(download) == m_manager->download_list()->end()) {
    // ATM doesn't really ever get here.
    delete download;

    m_slotFinished();
    return;
  }

  // Save the info-hash just in case the commands decide to delete it.
  torrent::HashString infohash = download->download()->info_hash();

  try {
    std::for_each(m_commands.begin(), m_commands.end(), rak::bind1st(std::ptr_fun(&rpc::parse_command_d_multiple_std), download));

    if (m_manager->download_list()->find(infohash) == m_manager->download_list()->end())
      throw torrent::input_error("The newly created download was removed.");

  } catch (torrent::input_error& e) {
    std::string msg = "Command on torrent creation failed: " + std::string(e.what());

    if (m_printLog) {
      m_manager->get_log_important().push_front(msg);
      m_manager->get_log_complete().push_front(msg);
    }
    
    if (m_manager->download_list()->find(infohash) != m_manager->download_list()->end()) {
      // Should stop it, mark it bad. Perhaps even delete it?
      download->set_hash_failed(true);
      download->set_message(msg);
      //     m_manager->download_list()->erase(m_manager->download_list()->find(infohash.data()));
    }

    return m_slotFinished();
  }

  // When a download scheduler is implemented, this is handled by the
  // above insertion into download list.
  if (m_session) {
    // This torrent was queued for hashing or hashing when the session
    // file was saved. Or it was in a started state.
    if (rpc::call_command_d_value("get_d_hashing", download) != Download::variable_hashing_stopped ||
        rpc::call_command_d_value("get_d_state", download) != 0)
      m_manager->download_list()->resume(download);

  } else {
    // Use the state thingie here, move below.
    if (m_start)
      m_manager->download_list()->start_normal(download);

    m_manager->download_store()->save(download);
  }

  m_slotFinished();
}