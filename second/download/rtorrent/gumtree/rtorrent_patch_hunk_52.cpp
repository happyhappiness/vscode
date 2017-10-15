 
     m_canvas->print(x, y, "%c %s",
 		    range.first == *m_focus ? '*' : ' ',
 		    p.get_dns().c_str());
     x += 18;
 
-    m_canvas->print(x, y, "%.1f", (double)p.get_rate_up() / 1024);
-    x += 7;
-
-    m_canvas->print(x, y, "%.1f", (double)p.get_rate_down() / 1024);
-    x += 7;
-
-    m_canvas->print(x, y, "%.1f", (double)p.get_rate_peer() / 1024);
-    x += 7;
+    m_canvas->print(x, y, "%.1f", (double)p.get_write_rate().rate() / 1024); x += 7;
+    m_canvas->print(x, y, "%.1f", (double)p.get_read_rate().rate() / 1024); x += 7;
+    m_canvas->print(x, y, "%.1f", (double)p.get_peer_rate().rate() / 1024); x += 7;
 
     m_canvas->print(x, y, "%c%c/%c%c",
 		    p.get_remote_choked() ? 'c' : 'u',
 		    p.get_remote_interested() ? 'i' : 'n',
 		    p.get_local_choked() ? 'c' : 'u',
 		    p.get_local_interested() ? 'i' : 'n');
