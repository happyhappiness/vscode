   y++;
 
   m_canvas->print(0, y++, "Connection Type: %s ( %s / %s )",
 		  core::Download::connection_type_to_string(m_download->get_connection_current()),
 		  core::Download::connection_type_to_string(m_download->get_connection_leech()),
 		  core::Download::connection_type_to_string(m_download->get_connection_seed()));
+  m_canvas->print(0, y++, "Tied to file: %s",
+		  m_download->tied_to_file().c_str());
 
   y++;
 
   if (*m_focus == m_list->end()) {
     m_canvas->print(0, y++, "No peer in focus");
 
     return;
   }
 
   m_canvas->print(0, y++, "*** Peer Info ***");
 
   m_canvas->print(0, y++, "DNS: %s:%hu", (*m_focus)->address().c_str(), (*m_focus)->port());
-  m_canvas->print(0, y++, "Id: %s" , utils::escape_string((*m_focus)->id()).c_str());
-  m_canvas->print(0, y++, "Options: %s" , utils::string_to_hex(std::string((*m_focus)->options(), 8)).c_str());
+  m_canvas->print(0, y++, "Id: %s" , rak::copy_escape_html((*m_focus)->id()).c_str());
+  m_canvas->print(0, y++, "Options: %s" , rak::transform_hex(std::string((*m_focus)->options(), 8)).c_str());
   m_canvas->print(0, y++, "Snubbed: %s", (*m_focus)->is_snubbed() ? "yes" : "no");
   m_canvas->print(0, y++, "Connected: %s", (*m_focus)->is_incoming() ? "remote" : "local");
 
   m_canvas->print(0, y++, "Done: %i%", done_percentage(**m_focus));
 
   m_canvas->print(0, y++, "Rate: %5.1f/%5.1f KB Total: %.1f/%.1f MB",
