void
ElementMenu::entry_prev() {
  if (empty() || (size() == 1 && m_entry == 0))
    return;

  unfocus_entry(m_entry);

  if (--m_entry >= size())
    m_entry = size() - 1;

  focus_entry(m_entry);
  base_type::operator[](m_entry).m_slotFocus();

  m_window->mark_dirty();
}