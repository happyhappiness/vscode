 					(int)m_download->download()->peers_currently_unchoked(),
 					(int)m_download->download()->peers_currently_interested(),
 					(int)m_download->download()->peers_complete(),
 					(int)m_download->download()->peers_accounted(),
 					(int)m_download->chunks_failed()),
 			       0);
-//   position = buffer + std::max(snprintf(position, last - buffer, " Priority: %s",
-// 					core::Download::priority_to_string(m_download->variable()->get("priority").as_value())),
-// 			       0);
+
   m_canvas->print(0, 1, "%s", buffer);
 
   position = print_download_status(buffer, last, m_download);
   m_canvas->print(0, 2, "[%c:%i] %s",
 		  m_download->tracker_list()->is_busy() ? 'C' : ' ',
 		  (int)(m_download->download()->tracker_list().timeout() / 1000000),
