void
Download::activate_display(Display displayType, bool focusDisplay) {
  if (!is_active())
    throw torrent::internal_error("ui::Download::activate_display(...) !is_active().");

  if (displayType > DISPLAY_MAX_SIZE)
    throw torrent::internal_error("ui::Download::activate_display(...) out of bounds");

  if (focusDisplay == m_focusDisplay && displayType == m_state)
    return;

  display::Frame* frame = m_frame->frame(0);

  // Cleanup previous state.
  switch (m_state) {
  case DISPLAY_PEER_LIST:
  case DISPLAY_INFO:
  case DISPLAY_FILE_LIST:
  case DISPLAY_TRACKER_LIST:
  case DISPLAY_CHUNKS_SEEN:
  case DISPLAY_TRANSFER_LIST:
    m_uiArray[DISPLAY_MENU]->disable();
    m_uiArray[m_state]->disable();

    frame->clear();
    break;

  case DISPLAY_MENU:
  case DISPLAY_MAX_SIZE:
    break;
  }

  m_state = displayType;
  m_focusDisplay = focusDisplay;

  // Initialize new state.
  switch (displayType) {
  case DISPLAY_PEER_LIST:
  case DISPLAY_INFO:
  case DISPLAY_FILE_LIST:
  case DISPLAY_TRACKER_LIST:
  case DISPLAY_CHUNKS_SEEN:
  case DISPLAY_TRANSFER_LIST:
    frame->initialize_column(2);

    m_uiArray[DISPLAY_MENU]->activate(frame->frame(0), !focusDisplay);
    m_uiArray[displayType]->activate(frame->frame(1), focusDisplay);
    break;

  case DISPLAY_MENU:
  case DISPLAY_MAX_SIZE:
    break;
  }

  // Set title.
  switch (displayType) {
  case DISPLAY_MAX_SIZE: break;
  default: control->ui()->window_title()->set_title(m_download->download()->name()); break;
  }

  control->display()->adjust_layout();
}