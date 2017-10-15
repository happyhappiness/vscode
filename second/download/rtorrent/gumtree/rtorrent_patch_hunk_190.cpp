 
     m_canvas->print(x, y, "%.1f", (double)p.up_rate()->rate() / 1024); x += 7;
     m_canvas->print(x, y, "%.1f", (double)p.down_rate()->rate() / 1024); x += 7;
     m_canvas->print(x, y, "%.1f", (double)p.peer_rate()->rate() / 1024); x += 7;
 
     m_canvas->print(x, y, "%c/%c%c/%c%c",
-                    p.is_incoming() ? 'r' : 'l',
+                    p.is_encrypted() ? (p.is_incoming() ? 'R' : 'L') : (p.is_incoming() ? 'r' : 'l'),
                     p.is_remote_choked() ? 'c' : 'u',
                     p.is_remote_interested() ? 'i' : 'n',
                     p.is_local_choked() ? 'c' : 'u',
                     p.is_local_interested() ? 'i' : 'n');
     x += 9;
 
