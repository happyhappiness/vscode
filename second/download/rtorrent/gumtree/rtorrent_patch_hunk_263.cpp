 void
 WindowTrackerList::redraw() {
   // TODO: Make this depend on tracker signal.
   m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
   m_canvas->erase();
 
-  int pos = 0;
+  unsigned int pos = 0;
   torrent::TrackerList* tl = m_download->tracker_list();
 
   m_canvas->print(2, pos, "Trackers: [Key: %08x]", tl->key());
   ++pos;
 
   if (tl->size() == 0 || *m_focus >= tl->size())
     return;
 
   typedef std::pair<unsigned int, unsigned int> Range;
 
-  unsigned int group = 0;
-  Range range = rak::advance_bidirectional<unsigned int>(0, *m_focus, tl->size(), (m_canvas->height() + 1) / 2);
+  Range range = rak::advance_bidirectional<unsigned int>(0, *m_focus, tl->size(), (m_canvas->height() - 1) / 2);
+  unsigned int group = tl->at(range.first)->group();
 
   while (range.first != range.second) {
     torrent::Tracker* tracker = tl->at(range.first);
 
 //     m_canvas->print(0, pos, "[%c] [S/L %5i/%5i] %s",
 //                     tracker->is_enabled() ? (tracker->is_open() ? '*' : ' ') : '-',
