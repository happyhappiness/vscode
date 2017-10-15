WindowDownloadStatusbar::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());

  m_canvas->erase();

  char buffer[m_canvas->width()];
  char* last = buffer + m_canvas->width() - 2;

  print_download_info(buffer, last, m_download);
  m_canvas->print(0, 0, "%s", buffer);

  snprintf(buffer, last - buffer, "Peers: %i(%i) Min/Max: %i/%i Slots: U:%i/%i D:%i/%i U/I/C/A: %i/%i/%i/%i Unchoked: %u/%u Failed: %i",
           (int)m_download->download()->connection_list()->size(),
           (int)m_download->download()->peer_list()->available_list_size(),
           (int)m_download->download()->connection_list()->min_size(),
           (int)m_download->download()->connection_list()->max_size(),
           (int)m_download->download()->uploads_min(),
           (int)m_download->download()->uploads_max(),
           (int)m_download->download()->downloads_min(),
           (int)m_download->download()->downloads_max(),
           (int)m_download->download()->peers_currently_unchoked(),
           (int)m_download->download()->peers_currently_interested(),
           (int)m_download->download()->peers_complete(),
           (int)m_download->download()->peers_accounted(),
           (int)m_download->info()->upload_unchoked(),
           (int)m_download->info()->download_unchoked(),
           (int)m_download->chunks_failed());

  m_canvas->print(0, 1, "%s", buffer);

  print_download_status(buffer, last, m_download);
  m_canvas->print(0, 2, "[%c:%i] %s",
                  m_download->tracker_list()->has_active() ? 'C' : ' ',
                  (int)(m_download->download()->tracker_controller()->seconds_to_next_timeout()),
                  buffer);
}

