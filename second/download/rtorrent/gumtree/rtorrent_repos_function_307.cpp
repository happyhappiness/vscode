void
Download::disable() {
  if (!is_active())
    throw torrent::internal_error("ui::Download::disable() called on an already disabled object.");

  control->input()->erase(&m_bindings);

  activate_display_focus(DISPLAY_MAX_SIZE);

  m_windowDownloadStatus->set_active(false);
  m_frame->clear();

  m_frame = NULL;
}