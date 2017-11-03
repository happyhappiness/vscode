void
ElementFileList::activate_display(Display display) {
  if (display == m_state)
    return;

  switch (m_state) {
  case DISPLAY_INFO:
    m_elementInfo->disable();
    break;

  case DISPLAY_LIST:
    m_window->set_active(false);
    m_frame->clear();
    break;

  case DISPLAY_MAX_SIZE:
    break;
  }

  m_state = display;

  switch (m_state) {
  case DISPLAY_INFO:
    m_elementInfo->activate(m_frame, true);
    break;

  case DISPLAY_LIST:
    m_window->set_active(true);
    m_frame->initialize_window(m_window);
    break;

  case DISPLAY_MAX_SIZE:
    break;
  }

  control->display()->adjust_layout();
}