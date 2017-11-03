void
ElementFileList::receive_select() {
  if (m_window == NULL || m_state != DISPLAY_LIST)
    return;

  if (is_collapsed() && !m_selected.is_file()) {
    m_selected++;
    m_window->mark_dirty();
  } else {
    activate_display(DISPLAY_INFO);
  }
}