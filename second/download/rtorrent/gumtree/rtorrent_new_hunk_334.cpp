           (int)m_download->download()->peers_currently_unchoked(),
           (int)m_download->download()->peers_currently_interested(),
           (int)m_download->download()->peers_complete(),
           (int)m_download->download()->peers_accounted(),
           (int)m_download->info()->upload_unchoked(),
           (int)m_download->info()->download_unchoked(),
           (int)m_download->download()->transfer_list()->failed_count());

  m_canvas->print(0, 1, "%s", buffer);

  print_download_status(buffer, last, m_download);
  m_canvas->print(0, 2, "[%c:%i] %s",
                  m_download->tracker_list()->has_active() ? 'C' : ' ',
