     if (m_manager->download_list()->find(infohash) != m_manager->download_list()->end()) {
       // Should stop it, mark it bad. Perhaps even delete it?
       download->set_hash_failed(true);
       download->set_message(msg);
       //     m_manager->download_list()->erase(m_manager->download_list()->find(infohash.data()));
     }
-
-    return m_slotFinished();
-  }
-
-  // When a download scheduler is implemented, this is handled by the
-  // above insertion into download list.
-  if (m_session) {
-    // This torrent was queued for hashing or hashing when the session
-    // file was saved. Or it was in a started state.
-    if (rpc::call_command_value("d.get_hashing", rpc::make_target(download)) != Download::variable_hashing_stopped ||
-        rpc::call_command_value("d.get_state", rpc::make_target(download)) != 0)
-      m_manager->download_list()->resume(download);
-
-  } else {
-    // Use the state thingie here, move below.
-    if (m_start)
-      m_manager->download_list()->start_normal(download);
-
-    m_manager->download_store()->save(download);
   }
 
   m_slotFinished();
 }
 
 void
