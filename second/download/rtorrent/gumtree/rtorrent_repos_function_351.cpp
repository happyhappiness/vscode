void
DownloadList::receive_download_erased(core::Download* d) {
  if (m_state != DISPLAY_DOWNLOAD || current_view()->focus() == current_view()->end_visible() || *current_view()->focus() != d)
    return;

  activate_display(DISPLAY_DOWNLOAD_LIST);
}