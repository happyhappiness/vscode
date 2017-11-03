void
apply_enable_trackers(int64_t arg) {
  for (core::Manager::DListItr itr = control->core()->download_list()->begin(), last = control->core()->download_list()->end(); itr != last; ++itr) {
    torrent::TrackerList tl = (*itr)->download()->tracker_list();

    for (int i = 0, last = tl.size(); i < last; ++i)
      if (arg)
        tl.get(i).enable();
      else
        tl.get(i).disable();

    if (arg && !rpc::call_command_value("get_use_udp_trackers"))
      (*itr)->enable_udp_trackers(false);
  }    
}