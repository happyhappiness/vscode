  char* position;
  char* last = buffer + m_canvas->get_width() - 2;

  position = print_download_info(buffer, last, m_download);
  m_canvas->print(0, 0, "%s", buffer);

  position = buffer + std::max(snprintf(buffer, last - buffer, "Peers: %i(%i) Min/Max: %i/%i Uploads: %i U/I: %i/%i Failed: %i",
					(int)m_download->get_download().peers_connected(),
					(int)m_download->get_download().peers_not_connected(),
					(int)m_download->get_download().peers_min(),
					(int)m_download->get_download().peers_max(),
					(int)m_download->get_download().uploads_max(),
					(int)m_download->get_download().peers_currently_unchoked(),
					(int)m_download->get_download().peers_currently_interested(),
					(int)m_download->chunks_failed()),
			       0);
//   position = buffer + std::max(snprintf(position, last - buffer, " Priority: %s",
// 					core::Download::priority_to_string(m_download->variables()->get("priority").as_value())),
// 			       0);
  m_canvas->print(0, 1, "%s", buffer);

  position = print_download_status(buffer, last, m_download);
  m_canvas->print(0, 2, "[%c:%i] %s",
		  m_download->get_download().is_tracker_busy() ? 'C' : ' ',
		  (int)(m_download->get_download().tracker_timeout() / 1000000),
		  buffer);
}

}
