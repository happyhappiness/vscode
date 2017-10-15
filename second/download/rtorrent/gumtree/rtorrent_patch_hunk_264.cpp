     if (tracker->group() == group)
       m_canvas->print(0, pos, "%2i:", group++);
 
     m_canvas->print(4, pos++, "%s",
                     tracker->url().c_str());
 
-    m_canvas->print(4, pos++, "Id: %s Focus: %s Enabled: %s Open: %s S/L: %u/%u",
-                    rak::copy_escape_html(tracker->tracker_id()).c_str(),
-                    range.first == tl->focus_index() ? "yes" : " no",
-                    tracker->is_usable() ? "yes" : tracker->is_enabled() ? "off" : " no",
-                    tracker->is_busy() ? "yes" : " no",
-                    tracker->scrape_complete(),
-                    tracker->scrape_incomplete());
+    if (pos < m_canvas->height())
+      m_canvas->print(4, pos++, "Id: %s Focus: %s Enabled: %s Open: %s S/L: %u/%u",
+                      rak::copy_escape_html(tracker->tracker_id()).c_str(),
+                      range.first == tl->focus_index() ? "yes" : " no",
+                      tracker->is_usable() ? "yes" : tracker->is_enabled() ? "off" : " no",
+                      tracker->is_busy() ? "yes" : " no",
+                      tracker->scrape_complete(),
+                      tracker->scrape_incomplete());
 
 //     m_canvas->print(4, pos++, "Id: %s Focus: %s Enabled: %s Open: %s Timer: %u/%u",
 //                     rak::copy_escape_html(tracker->tracker_id()).c_str(),
 //                     range.first == tl->focus() ? "yes" : " no",
 //                     tracker->is_enabled() ? "yes" : " no",
 //                     tracker->is_open() ? "yes" : " no",
