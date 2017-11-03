void
ElementMenu::push_back(const char* name, const slot_type& slotSelect, const slot_type& slotFocus) {
  iterator entry = base_type::insert(end(), value_type());

  entry->m_element    = new display::TextElementCString(name);
  entry->m_slotSelect = slotSelect;
  entry->m_slotFocus  = slotFocus;

  m_window->push_back(NULL);
  m_window->push_back(entry->m_element);

  // For the moment, don't bother doing anything if the window is
  // already active.
  m_window->mark_dirty();
}