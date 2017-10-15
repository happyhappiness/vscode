   m_canvas->print(0, y++, "Chunks:  %u / %u * %u",
 		  d.chunks_done(),
 		  d.chunks_total(),
 		  d.chunks_size());
 
   char buffer[32], *position;
-  position = print_ddmmyyyy(buffer, 32, static_cast<time_t>(d.creation_date()));
-  position = print_string(position, buffer + 32 - position, " ");
-  position = print_hhmmss(position, buffer + 32 - position, static_cast<time_t>(d.creation_date()));
+  position = print_ddmmyyyy(buffer, buffer + 32, static_cast<time_t>(d.creation_date()));
+  position = print_string(position, buffer + 32, " ");
+  position = print_hhmmss(position, buffer + 32, static_cast<time_t>(d.creation_date()));
 
   m_canvas->print(0, y++, "Created: %s", buffer);
 
   y++;
 
   m_canvas->print(0, y++, "Connection Type: %s ( %s / %s )",
-		  core::Download::connection_type_to_string(m_download->get_connection_current()),
-		  core::Download::connection_type_to_string(m_download->get_connection_leech()),
-		  core::Download::connection_type_to_string(m_download->get_connection_seed()));
-  m_canvas->print(0, y++, "Tied to file: %s",
-		  m_download->tied_to_file().c_str());
+		  m_download->variables()->get("connection_current").as_string().c_str(),
+		  m_download->variables()->get("connection_seed").as_string().c_str(),
+		  m_download->variables()->get("connection_leech").as_string().c_str());
+  m_canvas->print(0, y++, "Priority:        %u", torrent::download_priority(m_download->get_download()));
+
+  m_canvas->print(0, y++, "Directory:       %s", m_download->variable_string("directory").c_str());
+  m_canvas->print(0, y++, "Tied to file:    %s", m_download->variable_string("tied_to_file").c_str());
 
   y++;
 
   if (*m_focus == m_list->end()) {
     m_canvas->print(0, y++, "No peer in focus");
 
