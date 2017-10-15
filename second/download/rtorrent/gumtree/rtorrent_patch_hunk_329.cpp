   }
 
   m_slotFinished();
 }
 
 void
+DownloadFactory::log_created(Download* download, torrent::Object* rtorrent) {
+  std::stringstream dump;
+
+  dump << "info_hash = " << torrent::hash_string_to_hex_str(download->info()->hash()) << std::endl;
+  dump << "session = " << (m_session ? "true" : "false") << std::endl;
+
+  if (download->download()->info()->is_meta_download())
+    dump << "magnet = true" << std::endl;
+
+  if (!rtorrent->has_key_string("directory"))
+    dump << "directory = \"" << (m_variables["directory"].is_string() ? m_variables["directory"].as_string() : std::string()) << '"' << std::endl;
+  else
+    dump << "directory_base = \"" << (rtorrent->get_key("directory").is_string() ? rtorrent->get_key("directory").as_string() : std::string()) << '"' << std::endl;
+
+  dump << "---COMMANDS---" << std::endl;
+
+  for (command_list_type::const_iterator itr = m_commands.begin(); itr != m_commands.end(); itr++) {
+    dump << *itr << std::endl;
+  }
+
+  std::string dump_str = dump.str();
+
+  lt_log_print_dump(torrent::LOG_TORRENT_DEBUG, dump_str.c_str(), dump_str.size(), "Creating new download:");
+}
+
+void
 DownloadFactory::receive_failed(const std::string& msg) {
   // Add message to log.
   if (m_printLog)
     m_manager->push_log_std(msg + ": \"" + m_uri + "\"");
 
   m_slotFinished();
