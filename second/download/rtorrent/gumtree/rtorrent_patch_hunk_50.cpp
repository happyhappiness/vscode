 void
 WindowDownloadStatusbar::redraw() {
   utils::displayScheduler.insert(&m_taskUpdate, utils::Timer::cache().round_seconds() + 1000000);
 
   m_canvas->erase();
 
-  if (m_download->get_download().get_chunks_done() != m_download->get_download().get_chunks_total() || !m_download->get_download().is_open())
-    m_canvas->print(0, 0, "Torrent: %.1f / %.1f MiB Rate: %5.1f / %5.1f KiB Uploaded: %.1f MiB",
-		    (double)m_download->get_download().get_bytes_done() / (double)(1 << 20),
-		    (double)m_download->get_download().get_bytes_total() / (double)(1 << 20),
-		    (double)m_download->get_download().get_rate_up() / 1024.0,
-		    (double)m_download->get_download().get_rate_down() / 1024.0,
-		    (double)m_download->get_download().get_bytes_up() / (double)(1 << 20));
+  char buffer[m_canvas->get_width() - 2];
+  char* position;
+  char* last = buffer + m_canvas->get_width() - 2;
+
+  position = print_download_info(buffer, last - buffer, m_download);
+  m_canvas->print(0, 0, "%s", buffer);
+
+//   if (m_download->get_download().get_chunks_done() != m_download->get_download().get_chunks_total() || !m_download->get_download().is_open())
+//     m_canvas->print(0, 0, "Torrent: %.1f / %.1f MiB Rate: %5.1f / %5.1f KiB Uploaded: %.1f MiB",
+// 		    (double)m_download->get_download().get_bytes_done() / (double)(1 << 20),
+// 		    (double)m_download->get_download().get_bytes_total() / (double)(1 << 20),
+// 		    (double)m_download->get_download().get_write_rate().rate() / 1024.0,
+// 		    (double)m_download->get_download().get_read_rate().rate() / 1024.0,
+// 		    (double)m_download->get_download().get_write_rate().total() / (double)(1 << 20));
  
-  else
-    m_canvas->print(0, 0, "Torrent: Done %.1f MiB Rate: %5.1f / %5.1f KiB Uploaded: %.1f MiB",
-		    (double)m_download->get_download().get_bytes_total() / (double)(1 << 20),
-		    (double)m_download->get_download().get_rate_up() / 1024.0,
-		    (double)m_download->get_download().get_rate_down() / 1024.0,
-		    (double)m_download->get_download().get_bytes_up() / (double)(1 << 20));
+//   else
+//     m_canvas->print(0, 0, "Torrent: Done %.1f MiB Rate: %5.1f / %5.1f KiB Uploaded: %.1f MiB",
+// 		    (double)m_download->get_download().get_bytes_total() / (double)(1 << 20),
+// 		    (double)m_download->get_download().get_write_rate().rate() / 1024.0,
+// 		    (double)m_download->get_download().get_read_rate().rate() / 1024.0,
+// 		    (double)m_download->get_download().get_write_rate().total() / (double)(1 << 20));
     
   m_canvas->print(0, 1, "Peers: %i(%i) Min/Max: %i/%i Uploads: %i",
 		  (int)m_download->get_download().get_peers_connected(),
 		  (int)m_download->get_download().get_peers_not_connected(),
 		  (int)m_download->get_download().get_peers_min(),
 		  (int)m_download->get_download().get_peers_max(),
 		  (int)m_download->get_download().get_uploads_max());
 
+  position = print_download_status(buffer, last - buffer, m_download);
   m_canvas->print(0, 2, "[%c:%i] %s",
 		  m_download->get_download().is_tracker_busy() ? 'C' : ' ',
 		  (int)(m_download->get_download().get_tracker_timeout() / 1000000),
-		  print_download_status(m_download).c_str());
+		  buffer);
 }
 
 }
