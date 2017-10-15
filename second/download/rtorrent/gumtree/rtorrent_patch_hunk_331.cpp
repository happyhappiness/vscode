       download->set_hash_failed(true);
       download->set_message(msg);
       //     m_manager->download_list()->erase(m_manager->download_list()->find(infohash.data()));
     }
   }
 
-  m_slotFinished();
+  m_slot_finished();
 }
 
 void
 DownloadFactory::log_created(Download* download, torrent::Object* rtorrent) {
   std::stringstream dump;
 
