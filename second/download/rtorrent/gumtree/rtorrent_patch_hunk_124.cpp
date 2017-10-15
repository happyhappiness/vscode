     x += 6;
 
     m_canvas->print(x, y, "%3i", done_percentage(*range.first));
     x += 6;
 
     if (p.incoming_queue_size())
-      m_canvas->print(x, y, "%i", p.incoming_index(0));
+      m_canvas->print(x, y, "%i", p.incoming_queue(0)->index());
 
     x += 6;
 
     if (p.is_snubbed())
       m_canvas->print(x, y, "*");
 
+    x += 5;
+
+    char buf[128];
+    control->client_info()->print(buf, buf + 128, p.id().c_str());
+
+    m_canvas->print(x, y, "%s", buf);
+
     ++y;
     ++range.first;
   }
 }
 
 int
 WindowPeerList::done_percentage(torrent::Peer& p) {
-  int chunks = m_download->get_download().chunks_total();
+  int chunks = m_download->download()->chunks_total();
 
   return chunks ? (100 * p.chunks_done()) / chunks : 0;
 }
 
 }
