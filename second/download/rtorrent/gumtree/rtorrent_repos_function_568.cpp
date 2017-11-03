static void
connect_signal_tracker_dump(Download* d, torrent::Download::slot_dump_type s) {
  if (!rpc::call_command_string("get_tracker_dump").empty())
    d->download()->signal_tracker_dump(s);
}