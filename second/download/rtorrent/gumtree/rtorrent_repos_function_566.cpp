static void
connect_signal_network_log(Download* d, torrent::Download::slot_string_type s) {
  d->download()->signal_network_log(s);
}