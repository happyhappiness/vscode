void
DownloadList::activate_display(Display displayType) {
  if (!is_active())
    throw torrent::internal_error("ui::DownloadList::activate_display(...) !is_active().");

  if (displayType > DISPLAY_MAX_SIZE)
    throw torrent::internal_error("ui::DownloadList::activate_display(...) out of bounds");

  if (displayType == m_state)
    return;

  // Cleanup previous state.
  switch (m_state) {
  case DISPLAY_DOWNLOAD:
    m_uiArray[m_state]->disable();

    delete m_uiArray[m_state];
    m_uiArray[m_state] = NULL;

    break;
    
  case DISPLAY_DOWNLOAD_LIST:
    m_uiArray[DISPLAY_DOWNLOAD_LIST]->disable();

    m_windowLog->set_active(false);
    m_frame->frame(1)->clear();

    m_frame->clear();
    break;

  case DISPLAY_LOG:
  case DISPLAY_STRING_LIST:
    m_uiArray[m_state]->disable();
    break;
    
  default:
    break;
  }

  m_state = displayType;

  // Initialize new state.
  switch (displayType) {
  case DISPLAY_DOWNLOAD:
    // If no download has the focus, just return to the download list.
    if (current_view()->focus() == current_view()->end_visible()) {
      m_state = DISPLAY_MAX_SIZE;

      activate_display(DISPLAY_DOWNLOAD_LIST);
      return;

    } else {
      Download* download = new Download(*current_view()->focus());

      download->activate(m_frame);
      download->slot_exit(sigc::bind(sigc::mem_fun(*this, &DownloadList::activate_display), DISPLAY_DOWNLOAD_LIST));
    
      m_uiArray[DISPLAY_DOWNLOAD] = download;
      break;
    }

  case DISPLAY_DOWNLOAD_LIST:
    m_frame->initialize_row(2);

    m_uiArray[DISPLAY_DOWNLOAD_LIST]->activate(m_frame->frame(0));

    m_frame->frame(1)->initialize_window(m_windowLog);
    m_windowLog->set_active(true);
    m_windowLog->receive_update();
    break;

  case DISPLAY_LOG:
  case DISPLAY_STRING_LIST:
    m_uiArray[displayType]->activate(m_frame);
    break;

  default:
    break;
  }

  // Set title.
  switch (displayType) {
  case DISPLAY_DOWNLOAD_LIST: control->ui()->window_title()->set_title("rTorrent " VERSION " - libTorrent " + std::string(torrent::version())); break;
  case DISPLAY_LOG:           control->ui()->window_title()->set_title("Log"); break;
  default: break;
  }

  control->display()->adjust_layout();
}