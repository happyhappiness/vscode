   int pos = 0;
   torrent::TrackerList* tl = m_download->tracker_list();
 
   m_canvas->print(2, pos, "Trackers: [Key: %08x]", tl->key());
   ++pos;
 
-  if (tl->size() == 0)
+  if (tl->size() == 0 || *m_focus >= tl->size())
     return;
 
-  if (*m_focus >= tl->size())
-    throw std::logic_error("WindowTrackerList::redraw() called on an object with a bad focus value.");
-
   typedef std::pair<unsigned int, unsigned int> Range;
 
+  unsigned int group = 0;
   Range range = rak::advance_bidirectional<unsigned int>(0, *m_focus, tl->size(), (m_canvas->height() + 1) / 2);
 
   while (range.first != range.second) {
-    torrent::Tracker t = tl->get(range.first);
+    torrent::Tracker tracker = tl->get(range.first);
+
+//     m_canvas->print(0, pos, "[%c] [S/L %5i/%5i] %s",
+//                     tracker.is_enabled() ? (tracker.is_open() ? '*' : ' ') : '-',
+//                     tracker.scrape_complete(), tracker.scrape_incomplete(),
+//                     tracker.url().c_str());
+
+    if (tracker.group() == group)
+      m_canvas->print(0, pos, "%2i:", group++);
+
+    m_canvas->print(4, pos++, "%s",
+                    tracker.url().c_str());
 
-    m_canvas->print(0, pos++, "%c %s",
-                    range.first == *m_focus ? '*' : ' ',
-                    t.url().c_str());
-
-    m_canvas->print(0, pos++, "%c Group: %2i Id: %s Focus: %s Enabled: %s Open: %s S/L: %u/%u",
-                    range.first == *m_focus ? '*' : ' ',
-                    t.group(),
-                    rak::copy_escape_html(t.tracker_id()).c_str(),
+    m_canvas->print(4, pos++, "Id: %s Focus: %s Enabled: %s Open: %s S/L: %u/%u",
+                    rak::copy_escape_html(tracker.tracker_id()).c_str(),
                     range.first == tl->focus() ? "yes" : " no",
-                    t.is_enabled() ? "yes" : " no",
-                    t.is_open() ? "yes" : " no",
-                    t.scrape_complete(),
-                    t.scrape_incomplete());
+                    tracker.is_enabled() ? "yes" : " no",
+                    tracker.is_open() ? "yes" : " no",
+                    tracker.scrape_complete(),
+                    tracker.scrape_incomplete());
+
+//     m_canvas->print(4, pos++, "Id: %s Focus: %s Enabled: %s Open: %s Timer: %u/%u",
+//                     rak::copy_escape_html(tracker.tracker_id()).c_str(),
+//                     range.first == tl->focus() ? "yes" : " no",
+//                     tracker.is_enabled() ? "yes" : " no",
+//                     tracker.is_open() ? "yes" : " no",
+//                     tracker.normal_interval(),
+//                     tracker.min_interval());
+
+    if (range.first == *m_focus) {
+      m_canvas->set_attr(0, pos - 2, m_canvas->width(), is_focused() ? A_REVERSE : A_BOLD, COLOR_PAIR(0));
+      m_canvas->set_attr(0, pos - 1, m_canvas->width(), is_focused() ? A_REVERSE : A_BOLD, COLOR_PAIR(0));
+    }
 
-    ++range.first;
+    range.first++;
   }
 }
 
 }
