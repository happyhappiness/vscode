 
   Range range = rak::advance_bidirectional(m_list->begin(),
 					   *m_focus != m_list->end() ? *m_focus : m_list->begin(),
 					   m_list->end(),
 					   m_canvas->get_height() - y);
 
-  if (m_download->get_download().chunks_total() <= 0)
+  if (m_download->download()->chunks_total() <= 0)
     throw std::logic_error("WindowPeerList::redraw() m_slotChunksTotal() returned invalid value");
 
   while (range.first != range.second) {
     torrent::Peer& p = *range.first;
 
     x = 0;
 
     m_canvas->print(x, y, "%c %s",
 		    range.first == *m_focus ? '*' : ' ',
-		    p.address().c_str());
+		    rak::socket_address::cast_from(p.address())->address_str().c_str());
     x += 18;
 
     m_canvas->print(x, y, "%.1f", (double)p.up_rate()->rate() / 1024); x += 7;
     m_canvas->print(x, y, "%.1f", (double)p.down_rate()->rate() / 1024); x += 7;
     m_canvas->print(x, y, "%.1f", (double)p.peer_rate()->rate() / 1024); x += 7;
 
