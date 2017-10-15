   m_list(l),
   m_focus(f) {
 }
 
 void
 WindowPeerList::redraw() {
-  utils::displayScheduler.insert(&m_taskUpdate, utils::Timer::cache().round_seconds() + 1000000);
+  utils::displayScheduler.insert(&m_taskUpdate, (utils::Timer::cache() + 1000000).round_seconds());
   m_canvas->erase();
 
   int x = 2;
   int y = 0;
 
   m_canvas->print(x, y, "DNS");     x += 16;
