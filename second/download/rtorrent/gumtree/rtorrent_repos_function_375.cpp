void
ElementMenu::entry_select() {
  if (m_entry >= size())
    return;

  base_type::operator[](m_entry).m_slotSelect();
  m_window->mark_dirty();
}