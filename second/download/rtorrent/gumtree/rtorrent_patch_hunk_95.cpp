 		    range.first == *m_focus ? '*' : ' ',
 		    t.url().c_str());
 
     m_canvas->print(0, pos++, "%c Group: %2i Id: %s Focus: %s Enabled: %s Open: %s",
 		    range.first == *m_focus ? '*' : ' ',
 		    t.group(),
-		    utils::escape_string(t.tracker_id()).c_str(),
+		    rak::copy_escape_html(t.tracker_id()).c_str(),
 		    range.first == m_download->get_download().tracker_focus() ? "yes" : " no",
 		    t.is_enabled() ? "yes" : " no",
 		    t.is_open() ? "yes" : " no");
 
     ++range.first;
   }
