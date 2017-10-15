 WindowLog::find_older() {
   return m_log->find_older(utils::Timer::cache() - 60*1000000);
 }
 
 void
 WindowLog::redraw() {
-  m_nextDraw = utils::Timer::max();
-
   m_canvas->erase();
 
   int pos = 0;
 
   for (core::Log::iterator itr = m_log->begin(), end = find_older(); itr != end && pos < m_canvas->get_height(); ++itr)
     m_canvas->print(0, pos++, "(%s) %s",
