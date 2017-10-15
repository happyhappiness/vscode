   m_list(l),
   m_focus(f) {
 }
 
 void
 WindowDownloadList::redraw() {
-  if (utils::Timer::cache() - m_lastDraw < 1000000)
-    return;
-
-  m_lastDraw = utils::Timer::cache();
+  m_nextDraw = utils::Timer::cache().round_seconds() + 1000000;
 
   m_canvas->erase();
 
   if (m_list->empty())
     return;
 
-  DList::iterator itr, last;
-  
-  int pos = 0, y = 0;
-
-  if (*m_focus != m_list->end()) {
-    int i = 0;
-    itr = last = *m_focus;
-    
-    while (i < m_canvas->get_height() - y - 3 && !(itr == m_list->begin() && last == m_list->end())) {
-      if (last != m_list->end()) {
-	++last;
-	i += 3;
-      }
-
-      if (itr != m_list->begin() && i < m_canvas->get_height() - y - 3) {
-	--itr;
-	i += 3;
-      }
-    }
-
-  } else {
-    itr = m_list->begin();
-    last = m_list->end();
-  }    
+  typedef std::pair<DList::iterator, DList::iterator> Range;
+
+  Range range = utils::iterate_both_distance(m_list->begin(),
+					     *m_focus != m_list->end() ? *m_focus : m_list->begin(),
+					     m_list->end(),
+					     m_canvas->get_height() / 3);
+
+  // Make sure we properly fill out the last lines so it looks like
+  // there are more torrents, yet don't hide it if we got the last one
+  // in focus.
+  if (range.second != m_list->end())
+    ++range.second;
+
+  int pos = 0;
+
+  while (range.first != range.second) {
+    torrent::Download& d = (*range.first)->get_download();
 
-  while (itr != m_list->end() && y < m_canvas->get_height()) {
     m_canvas->print(0, pos++, "%c %s",
-		    itr == *m_focus ? '*' : ' ',
-		    (*itr)->get_download().get_name().c_str());
+		    range.first == *m_focus ? '*' : ' ',
+		    d.get_name().c_str());
 
-    if ((*itr)->get_download().get_chunks_done() != (*itr)->get_download().get_chunks_total() || !(*itr)->get_download().is_open())
-      m_canvas->print(0, pos++, "%c Torrent: %.1f / %.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
-		      itr == *m_focus ? '*' : ' ',
-		      (double)(*itr)->get_download().get_bytes_done() / (double)(1 << 20),
-		      (double)(*itr)->get_download().get_bytes_total() / (double)(1 << 20),
-		      (double)(*itr)->get_download().get_rate_up() / 1024.0,
-		      (double)(*itr)->get_download().get_rate_down() / 1024.0,
-		      (double)(*itr)->get_download().get_bytes_up() / (double)(1 << 20));
- 
-    else
+    if ((*range.first)->is_open() && (*range.first)->is_done())
       m_canvas->print(0, pos++, "%c Torrent: Done %.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
-		      itr == *m_focus ? '*' : ' ',
-		      (double)(*itr)->get_download().get_bytes_total() / (double)(1 << 20),
-		      (double)(*itr)->get_download().get_rate_up() / 1024.0,
-		      (double)(*itr)->get_download().get_rate_down() / 1024.0,
-		      (double)(*itr)->get_download().get_bytes_up() / (double)(1 << 20));
+		      range.first == *m_focus ? '*' : ' ',
+		      (double)d.get_bytes_total() / (double)(1 << 20),
+		      (double)d.get_rate_up() / 1024.0,
+		      (double)d.get_rate_down() / 1024.0,
+		      (double)d.get_bytes_up() / (double)(1 << 20));
+    else
+      m_canvas->print(0, pos++, "%c Torrent: %.1f / %.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
+		      range.first == *m_focus ? '*' : ' ',
+		      (double)d.get_bytes_done() / (double)(1 << 20),
+		      (double)d.get_bytes_total() / (double)(1 << 20),
+		      (double)d.get_rate_up() / 1024.0,
+		      (double)d.get_rate_down() / 1024.0,
+		      (double)d.get_bytes_up() / (double)(1 << 20));
     
-    m_canvas->print(0, pos++, "%c %s", itr == *m_focus ? '*' : ' ', print_download_status(*itr).c_str());
+    m_canvas->print(0, pos++, "%c %s",
+		    range.first == *m_focus ? '*' : ' ',
+		    print_download_status(*range.first).c_str());
 
-    ++itr;
+    ++range.first;
   }    
 }
 
 }
