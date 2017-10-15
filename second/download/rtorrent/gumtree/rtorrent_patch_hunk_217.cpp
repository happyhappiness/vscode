     delete download;
 
     m_slotFinished();
     return;
   }
 
+  // Save the info-hash just in case the commands decide to delete it.
+  torrent::HashString infohash = download->download()->info_hash();
+
+  try {
+    std::for_each(m_commands.begin(), m_commands.end(), rak::bind1st(std::ptr_fun(&rpc::parse_command_d_multiple_std), download));
+
+    if (m_manager->download_list()->find(infohash) == m_manager->download_list()->end())
+      throw torrent::input_error("The newly created download was removed.");
+
+  } catch (torrent::input_error& e) {
+    std::string msg = "Command on torrent creation failed: " + std::string(e.what());
+
+    if (m_printLog) {
+      m_manager->get_log_important().push_front(msg);
+      m_manager->get_log_complete().push_front(msg);
+    }
+    
+    if (m_manager->download_list()->find(infohash) != m_manager->download_list()->end()) {
+      // Should stop it, mark it bad. Perhaps even delete it?
+      download->set_hash_failed(true);
+      download->set_message(msg);
+      //     m_manager->download_list()->erase(m_manager->download_list()->find(infohash.data()));
+    }
+
+    return m_slotFinished();
+  }
+
   // When a download scheduler is implemented, this is handled by the
   // above insertion into download list.
   if (m_session) {
     // This torrent was queued for hashing or hashing when the session
     // file was saved. Or it was in a started state.
     if (rpc::call_command_d_value("get_d_hashing", download) != Download::variable_hashing_stopped ||
