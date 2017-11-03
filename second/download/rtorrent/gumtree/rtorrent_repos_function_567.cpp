static void
connect_signal_storage_log(Download* d, torrent::Download::slot_string_type s) {
  d->download()->signal_storage_error(s);
}