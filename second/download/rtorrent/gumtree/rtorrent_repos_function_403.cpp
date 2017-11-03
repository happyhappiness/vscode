void
ElementTransferList::receive_prev() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementTransferList::receive_prev(...) called on a disabled object");

  if (m_focus > 0)
    --m_focus;
  else
    m_focus = m_window->max_focus();

//   m_window->mark_dirty();
}