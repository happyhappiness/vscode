  char* last = buffer + m_canvas->width() - 2;

  position = print_download_info(buffer, last, m_download);
  m_canvas->print(0, 0, "%s", buffer);

  position = buffer + std::max(snprintf(buffer, last - buffer, "Peers: %i(%i) Min/Max: %i/%i Uploads: %i U/I/C/A: %i/%i/%i/%i Failed: %i",
                                        (int)m_download->download()->connection_list()->size(),
                                        (int)m_download->download()->peer_list()->available_list_size(),
                                        (int)m_download->download()->connection_list()->min_size(),
                                        (int)m_download->download()->connection_list()->max_size(),
                                        (int)m_download->download()->uploads_max(),
                                        (int)m_download->download()->peers_currently_unchoked(),
                                        (int)m_download->download()->peers_currently_interested(),
                                        (int)m_download->download()->peers_complete(),
                                        (int)m_download->download()->peers_accounted(),
                                        (int)m_download->chunks_failed()),
                               0);

  m_canvas->print(0, 1, "%s", buffer);

  position = print_download_status(buffer, last, m_download);
  m_canvas->print(0, 2, "[%c:%i] %s",
                  m_download->tracker_list()->has_active() ? 'C' : ' ',
                  (int)(m_download->download()->tracker_list()->time_next_connection()),
                  buffer);
}

}
