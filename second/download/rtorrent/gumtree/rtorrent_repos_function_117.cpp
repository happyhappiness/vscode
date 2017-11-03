torrent::Poll*
Control::poll() {
  return m_core->get_poll_manager()->get_torrent_poll();
}