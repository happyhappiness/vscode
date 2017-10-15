void
WindowStatusbar::redraw() {
  m_nextDraw = utils::Timer::cache().round_seconds() + 1000000;

  m_canvas->erase();

  int pos = 0;
  char buf[128];

  if (torrent::get(torrent::THROTTLE_ROOT_CONST_RATE) == 0)
    pos = snprintf(buf, 128, "off/");
  else
    pos = snprintf(buf, 128, "%3i/", (int)torrent::get(torrent::THROTTLE_ROOT_CONST_RATE) / 1024);

  if (torrent::get(torrent::THROTTLE_READ_CONST_RATE) == 0)
    pos = snprintf(buf + pos, 128 - pos, "off");
  else
    pos = snprintf(buf + pos, 128 - pos, "%-3i", (int)torrent::get(torrent::THROTTLE_READ_CONST_RATE) / 1024);

  m_canvas->print(0, 0, "Throttle U/D: %s Listen: %s:%i Handshakes: %i",
		  buf,
		  m_core->get_dns().empty() ? "<default>" : m_core->get_dns().c_str(),
		  (int)torrent::get(torrent::LISTEN_PORT),
		  (int)torrent::get(torrent::HANDSHAKES_TOTAL));
}