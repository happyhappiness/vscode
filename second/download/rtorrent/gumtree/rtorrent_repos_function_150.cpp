const char*
retrieve_d_priority_str(core::Download* download) {
  switch (download->priority()) {
  case 0:
    return "off";
  case 1:
    return "low";
  case 2:
    return "normal";
  case 3:
    return "high";
  default:
    throw torrent::input_error("Priority out of range.");
  }
}