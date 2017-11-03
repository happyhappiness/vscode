void
ElementText::push_back(text_element_wrapper entry) {
  m_window->push_back(entry.m_element);

  // For the moment, don't bother doing anything if the window is
  // already active.
  m_window->mark_dirty();
}