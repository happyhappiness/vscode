void
ElementMenu::set_entry(size_type idx, bool triggerSlot) {
  if (idx == m_entry)
    return;

  unfocus_entry(m_entry);

  m_entry = idx;
  focus_entry(m_entry);

  if (triggerSlot)
    base_type::operator[](m_entry).m_slotFocus();

  m_window->mark_dirty();
}