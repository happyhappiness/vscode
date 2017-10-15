   Window(new Canvas, false, 1),
   m_title(s) {
 }
 
 void
 WindowTitle::redraw() {
-  m_nextDraw = utils::Timer::cache().round_seconds() + 1000000;
+  utils::displayScheduler.insert(&m_taskUpdate, utils::Timer::cache().round_seconds() + 1000000);
   m_canvas->erase();
 
   m_canvas->print(std::max(0, (m_canvas->get_width() - (int)m_title.size()) / 2 - 4), 0,
 		  "*** %s ***", m_title.c_str());
 }
 
