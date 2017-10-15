 WindowLog::find_older() {
   return m_log->find_older(utils::Timer::cache() - 60*1000000);
 }
 
 void
 WindowLog::redraw() {
-  if (!is_dirty())
-    return;
-
-  m_lastDraw = utils::Timer::cache();
+  m_nextDraw = utils::Timer::max();
 
   m_canvas->erase();
 
   int pos = 0;
 
   //m_canvas->print(std::max(0, (int)m_canvas->get_width() / 2 - 5), pos++, "*** Log ***");
