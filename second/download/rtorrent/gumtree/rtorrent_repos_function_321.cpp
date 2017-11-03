void
Root::adjust_up_throttle(int throttle) {
  set_up_throttle(std::max<int>(torrent::up_throttle() / 1024 + throttle, 0));
}