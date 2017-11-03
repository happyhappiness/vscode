void
ElementStringList::next_screen() {
  if (m_window->get_draw_end() != m_list.end())
    m_window->set_range(m_window->get_draw_end(), m_list.end());
  else
    m_window->set_range(m_list.begin(), m_list.end());

  m_window->mark_dirty();
}