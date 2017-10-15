 
 void
 WindowInput::redraw() {
   if (!is_dirty())
     return;
 
-  m_lastDraw = Timer::cache();
+  m_lastDraw = utils::Timer::cache();
   m_canvas->erase();
 
   m_canvas->print(0, 0, "> %s", m_input->c_str());
 
   if (m_focus)
     m_canvas->set_attr(m_input->get_pos() + 2, 0, 1, A_REVERSE, COLOR_PAIR(0));
