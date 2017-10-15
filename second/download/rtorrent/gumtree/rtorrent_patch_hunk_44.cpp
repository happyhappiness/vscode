   m_list(l),
   m_focus(f) {
 }
 
 void
 WindowPeerInfo::redraw() {
-  m_nextDraw = utils::Timer::cache().round_seconds() + 1000000;
+  utils::displayScheduler.insert(&m_taskUpdate, utils::Timer::cache().round_seconds() + 1000000);
   m_canvas->erase();
 
   int y = 0;
   torrent::Download d = m_download->get_download();
 
   m_canvas->print(0, y++, "Hash:    %s", utils::string_to_hex(d.get_hash()).c_str());
