 
   if (m_view == NULL)
     return;
 
   m_canvas->print(0, 0, "%s", ("[View: " + m_view->name() + "]").c_str());
 
-  if (m_view->empty() || m_canvas->get_width() < 5 || m_canvas->get_height() < 2)
+  if (m_view->empty_visible() || m_canvas->get_width() < 5 || m_canvas->get_height() < 2)
     return;
 
   typedef std::pair<core::View::iterator, core::View::iterator> Range;
 
-  Range range = rak::advance_bidirectional(m_view->begin(),
-					   m_view->focus() != m_view->end() ? m_view->focus() : m_view->begin(),
-					   m_view->end(),
+  Range range = rak::advance_bidirectional(m_view->begin_visible(),
+					   m_view->focus() != m_view->end_visible() ? m_view->focus() : m_view->begin_visible(),
+					   m_view->end_visible(),
 					   m_canvas->get_height() / 3);
 
   // Make sure we properly fill out the last lines so it looks like
   // there are more torrents, yet don't hide it if we got the last one
   // in focus.
-  if (range.second != m_view->end())
+  if (range.second != m_view->end_visible())
     ++range.second;
 
   int pos = 1;
 
   while (range.first != range.second) {
     char buffer[m_canvas->get_width()];
