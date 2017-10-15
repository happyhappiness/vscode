 
 void
 WindowFileList::redraw() {
   m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
   m_canvas->erase();
 
-  torrent::FileList fl = m_download->download()->file_list();
+  torrent::FileList* fl = m_download->download()->file_list();
 
-  if (fl.size() == 0 || m_canvas->height() < 2)
+  if (fl->size_files() == 0 || m_canvas->height() < 2)
     return;
 
   int pos = 0;
 
   m_canvas->print( 2, pos, "File");
   m_canvas->print(55, pos, "Size");
