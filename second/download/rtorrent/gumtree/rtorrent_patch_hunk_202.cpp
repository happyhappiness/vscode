 
 void
 WindowFileList::redraw() {
   m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
   m_canvas->erase();
 
-  torrent::FileList* fl = m_download->download()->file_list();
+  torrent::FileList* fl = m_element->download()->download()->file_list();
 
   if (fl->size_files() == 0 || m_canvas->height() < 2)
     return;
 
-  unsigned int pos = 0;
-  iterator itr = rak::advance_bidirectional<iterator>(iterator(fl->begin()), *m_selected, iterator(fl->end()), m_canvas->height() - 1).first;
+  iterator entries[m_canvas->height() - 1];
+
+  unsigned int last = 0;
+
+  for (iterator itr = m_element->selected(); last != m_canvas->height() - 1; ) {
+    if (m_element->is_collapsed())
+      itr.forward_current_depth();
+    else
+      ++itr;
+
+    entries[last++] = itr;
+
+    if (itr == iterator(fl->end()))
+      break;
+  }
+
+  unsigned int first = m_canvas->height() - 1;
 
+  for (iterator itr = m_element->selected(); first >= last || first > (m_canvas->height() - 1) / 2; ) {
+    entries[--first] = itr;
+
+    if (itr == iterator(fl->begin()))
+      break;
+
+    if (m_element->is_collapsed())
+      itr.backward_current_depth();
+    else
+      --itr;
+  }
+
+  unsigned int pos = 0;
   m_canvas->print(0, pos++, "Cmp Pri  Size   Filename");
 
-  while (pos != m_canvas->height() && itr != iterator(fl->end())) {
+  while (pos != m_canvas->height()) {
+    iterator itr = entries[first];
+
+    if (itr == iterator(fl->end()))
+      break;
+
     if (itr.is_empty()) {
       m_canvas->print(16, pos, "EMPTY");
 
     } else if (itr.is_entering()) {
       m_canvas->print(16 + itr.depth(), pos, "\\ %s", 
                       itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");
