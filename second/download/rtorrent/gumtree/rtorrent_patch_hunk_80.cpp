 
   Range range = rak::advance_bidirectional(m_list->begin(),
 					   *m_focus != m_list->end() ? *m_focus : m_list->begin(),
 					   m_list->end(),
 					   m_canvas->get_height() - y);
 
-  if (m_download->get_download().get_chunks_total() <= 0)
+  if (m_download->get_download().chunks_total() <= 0)
     throw std::logic_error("WindowPeerList::redraw() m_slotChunksTotal() returned invalid value");
 
   while (range.first != range.second) {
     torrent::Peer& p = *range.first;
 
     x = 0;
 
     m_canvas->print(x, y, "%c %s",
 		    range.first == *m_focus ? '*' : ' ',
-		    p.get_dns().c_str());
+		    p.address().c_str());
     x += 18;
 
-    m_canvas->print(x, y, "%.1f", (double)p.get_up_rate().rate() / 1024); x += 7;
-    m_canvas->print(x, y, "%.1f", (double)p.get_down_rate().rate() / 1024); x += 7;
-    m_canvas->print(x, y, "%.1f", (double)p.get_peer_rate().rate() / 1024); x += 7;
+    m_canvas->print(x, y, "%.1f", (double)p.up_rate()->rate() / 1024); x += 7;
+    m_canvas->print(x, y, "%.1f", (double)p.down_rate()->rate() / 1024); x += 7;
+    m_canvas->print(x, y, "%.1f", (double)p.peer_rate()->rate() / 1024); x += 7;
 
     m_canvas->print(x, y, "%c/%c%c/%c%c",
 		    p.is_incoming() ? 'r' : 'l',
-		    p.get_remote_choked() ? 'c' : 'u',
-		    p.get_remote_interested() ? 'i' : 'n',
-		    p.get_local_choked() ? 'c' : 'u',
-		    p.get_local_interested() ? 'i' : 'n');
+		    p.is_remote_choked() ? 'c' : 'u',
+		    p.is_remote_interested() ? 'i' : 'n',
+		    p.is_local_choked() ? 'c' : 'u',
+		    p.is_local_interested() ? 'i' : 'n');
     x += 9;
 
     m_canvas->print(x, y, "%i/%i",
-		    p.get_outgoing_queue_size(),
-		    p.get_incoming_queue_size());
+		    p.outgoing_queue_size(),
+		    p.incoming_queue_size());
     x += 6;
 
     m_canvas->print(x, y, "%3i", done_percentage(*range.first));
     x += 6;
 
-    if (p.get_incoming_queue_size())
-      m_canvas->print(x, y, "%i", p.get_incoming_index(0));
+    if (p.incoming_queue_size())
+      m_canvas->print(x, y, "%i", p.incoming_index(0));
 
     x += 6;
 
-    if (p.get_snubbed())
+    if (p.is_snubbed())
       m_canvas->print(x, y, "*");
 
     ++y;
     ++range.first;
   }
 }
 
 int
 WindowPeerList::done_percentage(torrent::Peer& p) {
-  int chunks = m_download->get_download().get_chunks_total();
+  int chunks = m_download->get_download().chunks_total();
 
-  return chunks ? (100 * p.get_chunks_done()) / chunks : 0;
+  return chunks ? (100 * p.chunks_done()) / chunks : 0;
 }
 
 }
