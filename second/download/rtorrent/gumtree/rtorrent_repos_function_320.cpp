void
Root::adjust_down_throttle(int throttle) {
  set_down_throttle(std::max<int>(torrent::down_throttle() / 1024 + throttle, 0));
}