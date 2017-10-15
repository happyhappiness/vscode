		  (int)m_download->download()->peers_complete(),
		  (int)m_download->download()->peers_accounted(),
		  std::floor(m_download->distributed_copies() * 100.0f) / 100.0f);

  const uint8_t* seen = m_download->download()->chunks_seen();

  if (seen == NULL) {
    m_canvas->print(2, 2, "Not available.");
    return;
  }

  const uint8_t* chunk = seen;
  const uint8_t* last = seen + m_download->download()->chunks_total();

  const torrent::Bitfield* bitfield = m_download->download()->bitfield();

  for (int y = 1; y < m_canvas->get_height() && chunk < last; ++y) {
    m_canvas->print(0, y, "%5d ", (int)(chunk - seen));

    while (chunk < last) {
      chtype attr;

      if (bitfield->get(chunk - seen))
	attr = A_NORMAL;
//    else if (foo->is_downloading(chunk - seen))
//	attr = A_UNDERLINE;
      else
	attr = A_BOLD;

      m_canvas->print_char(attr | rak::value_to_hexchar<0>(std::min<uint8_t>(*chunk, 0xF)));
      chunk++;

      if ((chunk - seen) % 10 == 0) {
	if (m_canvas->get_x() + 12 > m_canvas->get_width())
