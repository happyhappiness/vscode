    rpc::commands.call_catch(m_session ? "event.download.inserted_session" : "event.download.inserted_new",
                             rpc::make_target(download), torrent::Object(), "Download event action failed: ");

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
