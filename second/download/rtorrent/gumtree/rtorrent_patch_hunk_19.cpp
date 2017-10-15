 
   ++y;
 
   if (m_list->empty())
     return;
 
-  PList::iterator itr, last;
-  
-  if (*m_focus != m_list->end()) {
-    int i = 0;
-    itr = last = *m_focus;
-    
-    while (i < m_canvas->get_height() - y && !(itr == m_list->begin() && last == m_list->end())) {
-      if (itr != m_list->begin()) {
-	--itr;
-	++i;
-      }
-      
-      if (last != m_list->end() && i < m_canvas->get_height() - y) {
-	++last;
-	++i;
-      }
-    }
-
-  } else {
-    itr = m_list->begin();
-    last = m_list->end();
-  }    
+  typedef std::pair<PList::iterator, PList::iterator> Range;
 
-  uint32_t chunksTotal = m_slotChunksTotal();
+  Range range = utils::iterate_both_distance(m_list->begin(),
+					     *m_focus != m_list->end() ? *m_focus : m_list->begin(),
+					     m_list->end(),
+					     m_canvas->get_height() - y);
 
-  if (chunksTotal <= 0)
+  if (m_download->get_download().get_chunks_total() <= 0)
     throw std::logic_error("WindowPeerList::redraw() m_slotChunksTotal() returned invalid value");
 
-  while (itr != m_list->end() && y < m_canvas->get_height()) {
+  while (range.first != range.second) {
+    torrent::Peer& p = *range.first;
+
     x = 0;
 
     m_canvas->print(x, y, "%c %s",
-	     itr == *m_focus ? '*' : ' ',
-	     itr->get_dns().c_str());
+		    range.first == *m_focus ? '*' : ' ',
+		    p.get_dns().c_str());
     x += 18;
 
-    m_canvas->print(x, y, "%.1f",
-	     (double)itr->get_rate_up() / 1024);
+    m_canvas->print(x, y, "%.1f", (double)p.get_rate_up() / 1024);
     x += 7;
 
-    m_canvas->print(x, y, "%.1f",
-	     (double)itr->get_rate_down() / 1024);
+    m_canvas->print(x, y, "%.1f", (double)p.get_rate_down() / 1024);
     x += 7;
 
-    m_canvas->print(x, y, "%.1f",
-	     (double)itr->get_rate_peer() / 1024);
+    m_canvas->print(x, y, "%.1f", (double)p.get_rate_peer() / 1024);
     x += 7;
 
     m_canvas->print(x, y, "%c%c/%c%c%c",
-	     itr->get_remote_choked() ? 'c' : 'u',
-	     itr->get_remote_interested() ? 'i' : 'n',
-	     itr->get_local_choked() ? 'c' : 'u',
-	     itr->get_local_interested() ? 'i' : 'n',
-	     itr->get_choke_delayed() ? 'd' : ' ');
+		    p.get_remote_choked() ? 'c' : 'u',
+		    p.get_remote_interested() ? 'i' : 'n',
+		    p.get_local_choked() ? 'c' : 'u',
+		    p.get_local_interested() ? 'i' : 'n',
+		    p.get_choke_delayed() ? 'd' : ' ');
     x += 7;
 
     m_canvas->print(x, y, "%i/%i",
-	     itr->get_outgoing_queue_size(),
-	     itr->get_incoming_queue_size());
+		    p.get_outgoing_queue_size(),
+		    p.get_incoming_queue_size());
     x += 6;
 
-    m_canvas->print(x, y, "%3i", (itr->get_chunks_done() * 100) / chunksTotal);
+    m_canvas->print(x, y, "%3i", done_percentage(*range.first));
     x += 6;
 
-    if (itr->get_incoming_queue_size())
-      m_canvas->print(x, y, "%i",
-	       itr->get_incoming_index(0));
+    if (p.get_incoming_queue_size())
+      m_canvas->print(x, y, "%i", p.get_incoming_index(0));
 
     x += 6;
 
-    if (itr->get_snubbed())
+    if (p.get_snubbed())
       m_canvas->print(x, y, "*");
 
     ++y;
-    ++itr;
+    ++range.first;
   }
 }
 
+int
+WindowPeerList::done_percentage(torrent::Peer& p) {
+  int chunks = m_download->get_download().get_chunks_total();
+
+  return chunks ? (100 * p.get_chunks_done()) / chunks : 0;
+}
+
 }
