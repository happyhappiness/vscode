void
WindowStatusbar::redraw() {
  utils::displayScheduler.insert(&m_taskUpdate, utils::Timer::cache().round_seconds() + 1000000);

  m_canvas->erase();

  // TODO: Make a buffer with size = get_width?
  int pos = 0;
  char buf[128];

  if (torrent::get_write_throttle() == 0)
    pos = snprintf(buf, 128, "off/");
  else
    pos = snprintf(buf, 128, "%3i/", torrent::get_write_throttle() / 1024);

  if (torrent::get_read_throttle() == 0)
    pos = snprintf(buf + pos, 128 - pos, "off");
  else
    pos = snprintf(buf + pos, 128 - pos, "%-3i", torrent::get_read_throttle() / 1024);

  m_canvas->print(0, 0, "Throttle U/D: %s  Rate: %5.1f / %5.1f KiB  Listen: %s:%i%s",
		  buf,
		  (double)torrent::get_write_rate().rate() / 1024.0,
		  (double)torrent::get_read_rate().rate() / 1024.0,
		  !torrent::get_address().empty() ? torrent::get_address().c_str() : "<default>",
		  (int)torrent::get_listen_port(),
		  !torrent::get_bind_address().empty() ? ("  Bind: " + torrent::get_bind_address()).c_str() : "");

  pos = snprintf(buf, 128, "[%3i/%3i/%3i]",
		 torrent::get_total_handshakes(),
		 torrent::get_open_sockets(),
		 torrent::get_max_open_sockets());

  m_canvas->print(m_canvas->get_width() - pos, 0, "%s", buf);
}