void
Root::set_down_throttle(unsigned int throttle) {
  if (m_windowStatusbar != NULL)
    m_windowStatusbar->mark_dirty();

  torrent::set_down_throttle(throttle * 1024);

  unsigned int div    = std::max<int>(rpc::call_command_value("get_max_downloads_div"), 0);
  unsigned int global = std::max<int>(rpc::call_command_value("get_max_downloads_global"), 0);

  if (throttle == 0 || div == 0) {
    torrent::set_max_download_unchoked(global);
    return;
  }

  throttle /= rpc::call_command_value("get_max_downloads_div");

  unsigned int maxUnchoked;

  if (throttle <= 10)
    maxUnchoked = 1 + throttle / 1;
  else
    maxUnchoked = 10 + throttle / 5;

  if (global != 0)
    torrent::set_max_download_unchoked(std::min(maxUnchoked, global));
  else
    torrent::set_max_download_unchoked(maxUnchoked);
}