void
ElementFileList::disable() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementFileList::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  activate_display(DISPLAY_MAX_SIZE);

  m_frame->clear();
  m_frame = NULL;

  delete m_window;
  m_window = NULL;

  delete m_elementInfo;
  m_elementInfo = NULL;
}