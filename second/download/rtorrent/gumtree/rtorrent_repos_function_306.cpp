void
Download::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error("ui::Download::activate() called on an already activated object.");

  control->input()->push_back(&m_bindings);

  m_frame = frame;
  m_frame->initialize_row(2);

  m_frame->frame(1)->initialize_window(m_windowDownloadStatus);
  m_windowDownloadStatus->set_active(true);

  activate_display_menu(DISPLAY_PEER_LIST);
}