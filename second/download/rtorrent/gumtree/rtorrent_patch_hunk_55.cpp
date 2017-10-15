   }
 
   m_canvas->print(0, y++, "*** Peer Info ***");
 
   m_canvas->print(0, y++, "DNS: %s:%hu", (*m_focus)->get_dns().c_str(), (*m_focus)->get_port());
   m_canvas->print(0, y++, "Id: %s" , utils::escape_string((*m_focus)->get_id()).c_str());
-  m_canvas->print(0, y++, "Snubbed: %s", (*m_focus)->get_snubbed() ? "Yes" : "No");
+  m_canvas->print(0, y++, "Options: %s" , utils::string_to_hex(std::string((*m_focus)->get_options(), 8)).c_str());
+  m_canvas->print(0, y++, "Snubbed: %s", (*m_focus)->get_snubbed() ? "yes" : "no");
+  m_canvas->print(0, y++, "Connected: %s", (*m_focus)->is_incoming() ? "remote" : "local");
 
   m_canvas->print(0, y++, "Done: %i%", done_percentage(**m_focus));
 
   m_canvas->print(0, y++, "Rate: %5.1f/%5.1f KB Total: %.1f/%.1f MB",
 		  (double)(*m_focus)->get_write_rate().rate() / (double)(1 << 10),
 		  (double)(*m_focus)->get_read_rate().rate() / (double)(1 << 10),
