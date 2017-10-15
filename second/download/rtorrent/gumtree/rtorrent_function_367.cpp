void
DownloadFactory::receive_success() {
  Download* download = m_stream != NULL ?
    m_manager->download_list()->create(m_stream, m_printLog) :
    m_manager->download_list()->create(m_object, m_printLog);

  m_object = NULL;

  if (download == NULL) {
    // core::Manager should already have added the error message to
    // the log.
    m_slotFinished();
    return;
  }

  torrent::Object* root = download->bencode();

  if (download->download()->info()->is_meta_download()) {
    torrent::Object& meta = root->insert_key("rtorrent_meta_download", torrent::Object::create_map());
    meta.insert_key("start", m_start);
    meta.insert_key("print_log", m_printLog);
 
    torrent::Object::list_type& commands = meta.insert_key("commands", torrent::Object::create_list()).as_list();

    for (command_list_type::iterator itr = m_commands.begin(); itr != m_commands.end(); ++itr)
      commands.push_back(*itr);
  }

  if (m_session) {
    download_factory_add_stream(root, "rtorrent", (rak::path_expand(m_uri) + ".rtorrent").c_str());
    download_factory_add_stream(root, "libtorrent_resume", (rak::path_expand(m_uri) + ".libtorrent_resume").c_str());
    
  } else {
    // We only allow session torrents to keep their
    // 'rtorrent/libtorrent' sections. The "fast_resume" section
    // should be safe to keep.
    root->erase_key("rtorrent");
  }

  torrent::Object* rtorrent = &root->insert_preserve_copy("rtorrent", torrent::Object::create_map()).first->second;
  torrent::Object& resumeObject = root->insert_preserve_copy("libtorrent_resume", torrent::Object::create_map()).first->second;

  initialize_rtorrent(download, rtorrent);

  if (!rtorrent->has_key_string("custom1")) rtorrent->insert_key("custom1", std::string());
  if (!rtorrent->has_key_string("custom2")) rtorrent->insert_key("custom2", std::string());
  if (!rtorrent->has_key_string("custom3")) rtorrent->insert_key("custom3", std::string());
  if (!rtorrent->has_key_string("custom4")) rtorrent->insert_key("custom4", std::string());
  if (!rtorrent->has_key_string("custom5")) rtorrent->insert_key("custom5", std::string());

  rpc::call_command("d.uploads_min.set",      rpc::call_command_void("throttle.min_uploads"), rpc::make_target(download));
  rpc::call_command("d.uploads_max.set",      rpc::call_command_void("throttle.max_uploads"), rpc::make_target(download));
  rpc::call_command("d.downloads_min.set",    rpc::call_command_void("throttle.min_downloads"), rpc::make_target(download));
  rpc::call_command("d.downloads_max.set",    rpc::call_command_void("throttle.max_downloads"), rpc::make_target(download));
  rpc::call_command("d.peers_min.set",        rpc::call_command_void("throttle.min_peers.normal"), rpc::make_target(download));
  rpc::call_command("d.peers_max.set",        rpc::call_command_void("throttle.max_peers.normal"), rpc::make_target(download));
  rpc::call_command("d.tracker_numwant.set",  rpc::call_command_void("trackers.numwant"), rpc::make_target(download));
  rpc::call_command("d.max_file_size.set",    rpc::call_command_void("system.file.max_size"), rpc::make_target(download));

  if (rpc::call_command_value("d.complete", rpc::make_target(download)) != 0) {
    if (rpc::call_command_value("throttle.min_peers.seed") >= 0)
      rpc::call_command("d.peers_min.set", rpc::call_command_void("throttle.min_peers.seed"), rpc::make_target(download));

    if (rpc::call_command_value("throttle.max_peers.seed") >= 0)
      rpc::call_command("d.peers_max.set", rpc::call_command_void("throttle.max_peers.seed"), rpc::make_target(download));
  }

  if (!rpc::call_command_value("trackers.use_udp"))
    download->enable_udp_trackers(false);

  // Check first if we already have these values set in the session
  // torrent, so that it is safe to change the values.
  //
  // Need to also catch the exceptions.
  if (rpc::call_command_value("system.file.split_size") >= 0)
    torrent::file_split_all(download->download()->file_list(),
                            rpc::call_command_value("system.file.split_size"),
                            rpc::call_command_string("system.file.split_suffix"));

  if (!rtorrent->has_key_string("directory"))
    rpc::call_command("d.directory.set", m_variables["directory"], rpc::make_target(download));
  else
    rpc::call_command("d.directory_base.set", rtorrent->get_key("directory"), rpc::make_target(download));

  if (!m_session && m_variables["tied_to_file"].as_value())
    rpc::call_command("d.tied_to_file.set", m_uri.empty() ? m_variables["tied_file"] : m_uri, rpc::make_target(download));

  rpc::call_command("d.peer_exchange.set", rpc::call_command_value("protocol.pex"), rpc::make_target(download));

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
  torrent::HashString infohash = download->info()->hash();

  try {
    std::for_each(m_commands.begin(), m_commands.end(),
                  rak::bind2nd(std::ptr_fun(&rpc::parse_command_multiple_std), rpc::make_target(download)));

    if (m_manager->download_list()->find(infohash) == m_manager->download_list()->end())
      throw torrent::input_error("The newly created download was removed.");

    if (!m_session)
       rpc::call_command("d.state.set", (int64_t)m_start, rpc::make_target(download));

    rpc::commands.call_catch(m_session ? "event.download.inserted_session" : "event.download.inserted_new",
                             rpc::make_target(download), torrent::Object(), "Download event action failed: ");

  } catch (torrent::input_error& e) {
    std::string msg = "Command on torrent creation failed: " + std::string(e.what());

    if (m_printLog)
      m_manager->push_log_std(msg);
    
    if (m_manager->download_list()->find(infohash) != m_manager->download_list()->end()) {
      // Should stop it, mark it bad. Perhaps even delete it?
      download->set_hash_failed(true);
      download->set_message(msg);
      //     m_manager->download_list()->erase(m_manager->download_list()->find(infohash.data()));
    }
  }

  m_slotFinished();
}