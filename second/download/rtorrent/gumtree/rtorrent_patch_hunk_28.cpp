   m_canvas->erase();
 
   int y = 0;
   torrent::Download d = m_download->get_download();
 
   m_canvas->print(0, y++, "Hash: %s", utils::string_to_hex(d.get_hash()).c_str());
+  m_canvas->print(0, y++, "Id:   %s", utils::escape_string(d.get_id()).c_str());
   m_canvas->print(0, y++, "Chunks: %u / %u * %u",
 		  d.get_chunks_done(),
 		  d.get_chunks_total(),
 		  d.get_chunks_size());
 
   y++;
