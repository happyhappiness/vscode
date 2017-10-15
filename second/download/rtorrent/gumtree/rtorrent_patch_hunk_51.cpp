   m_canvas->print(0, y++, "Id: %s" , utils::escape_string((*m_focus)->get_id()).c_str());
   m_canvas->print(0, y++, "Snubbed: %s", (*m_focus)->get_snubbed() ? "Yes" : "No");
 
   m_canvas->print(0, y++, "Done: %i%", done_percentage(**m_focus));
 
   m_canvas->print(0, y++, "Rate: %5.1f/%5.1f KB Total: %.1f/%.1f MB",
-		  (double)(*m_focus)->get_rate_up() / (double)(1 << 10),
-		  (double)(*m_focus)->get_rate_down() / (double)(1 << 10),
-		  (double)(*m_focus)->get_transfered_up() / (double)(1 << 20),
-		  (double)(*m_focus)->get_transfered_down() / (double)(1 << 20));
+		  (double)(*m_focus)->get_write_rate().rate() / (double)(1 << 10),
+		  (double)(*m_focus)->get_read_rate().rate() / (double)(1 << 10),
+		  (double)(*m_focus)->get_write_rate().total() / (double)(1 << 20),
+		  (double)(*m_focus)->get_read_rate().total() / (double)(1 << 20));
 }
 
 int
 WindowPeerInfo::done_percentage(torrent::Peer& p) {
   int chunks = m_download->get_download().get_chunks_total();
 
