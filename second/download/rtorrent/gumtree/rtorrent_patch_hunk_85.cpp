   m_list(l),
   m_focus(f) {
 }
 
 void
 WindowPeerInfo::redraw() {
-  utils::displayScheduler.insert(&m_taskUpdate, (utils::Timer::cache() + 1000000).round_seconds());
+  priority_queue_insert(&displayScheduler, &m_taskUpdate, (cachedTime + 1000000).round_seconds());
   m_canvas->erase();
 
   int y = 0;
   torrent::Download d = m_download->get_download();
 
   m_canvas->print(0, y++, "Hash:    %s", utils::string_to_hex(d.info_hash()).c_str());
