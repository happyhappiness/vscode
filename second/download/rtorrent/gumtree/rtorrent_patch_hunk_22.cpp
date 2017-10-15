 
     m_canvas->print(0, pos++, "%c %s",
 		    range.first == *m_focus ? '*' : ' ',
 		    d.get_name().c_str());
 
     if ((*range.first)->is_open() && (*range.first)->is_done())
-      m_canvas->print(0, pos++, "%c Torrent: Done %.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
+      m_canvas->print(0, pos++, "%c Torrent: Done %10.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
 		      range.first == *m_focus ? '*' : ' ',
 		      (double)d.get_bytes_total() / (double)(1 << 20),
 		      (double)d.get_rate_up() / 1024.0,
 		      (double)d.get_rate_down() / 1024.0,
 		      (double)d.get_bytes_up() / (double)(1 << 20));
     else
-      m_canvas->print(0, pos++, "%c Torrent: %.1f / %.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
+      m_canvas->print(0, pos++, "%c Torrent: %6.1f / %6.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
 		      range.first == *m_focus ? '*' : ' ',
 		      (double)d.get_bytes_done() / (double)(1 << 20),
 		      (double)d.get_bytes_total() / (double)(1 << 20),
 		      (double)d.get_rate_up() / 1024.0,
 		      (double)d.get_rate_down() / 1024.0,
 		      (double)d.get_bytes_up() / (double)(1 << 20));
