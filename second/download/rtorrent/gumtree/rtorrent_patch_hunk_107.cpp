   m_list(l),
   m_focus(f) {
 }
 
 void
 WindowPeerList::redraw() {
-  m_slotSchedule(this, (cachedTime + 1000000).round_seconds());
+  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());
   m_canvas->erase();
 
   int x = 2;
   int y = 0;
 
   m_canvas->print(x, y, "DNS");     x += 16;
