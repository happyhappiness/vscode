void
Root::set_up_throttle(unsigned int throttle) {
  if (m_windowStatusbar != NULL)
    m_windowStatusbar->mark_dirty();

  torrent::set_up_throttle(throttle * 1024);

  unsigned int div    = std::max<int>(rpc::call_command_value("get_max_uploads_div"), 0);
  unsigned int global = std::max<int>(rpc::call_command_value("get_max_uploads_global"), 0);

  if (throttle == 0 || div == 0) {
    torrent::set_max_unchoked(global);
    return;
  }

  throttle /= rpc::call_command_value("get_max_uploads_div");

  unsigned int maxUnchoked;

  if (throttle <= 10)
    maxUnchoked = 1 + throttle / 1;
  else
    maxUnchoked = 10 + throttle / 5;

  if (global != 0)
    torrent::set_max_unchoked(std::min(maxUnchoked, global));
  else
    torrent::set_max_unchoked(maxUnchoked);
}