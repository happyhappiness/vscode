   m_focus(focus) {
 }
 
 void
 WindowTrackerList::redraw() {
   // TODO: Make this depend on tracker signal.
-  m_nextDraw = utils::Timer::cache().round_seconds() + 10 * 1000000;
+  utils::displayScheduler.insert(&m_taskUpdate, utils::Timer::cache().round_seconds() + 10 * 1000000);
   m_canvas->erase();
 
   int pos = 0;
 
   m_canvas->print( 2, pos, "Trackers:");
 
