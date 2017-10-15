   m_list(l),
   m_focus(f) {
 }
 
 void
 WindowPeerInfo::redraw() {
-  m_slotSchedule(this, (cachedTime + 1000000).round_seconds());
+  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());
   m_canvas->erase();
 
   int y = 0;
   torrent::Download d = m_download->get_download();
 
   m_canvas->print(0, y++, "Hash:    %s", rak::transform_hex(d.info_hash()).c_str());
