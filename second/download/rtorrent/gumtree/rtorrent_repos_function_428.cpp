void
Download::enable_udp_trackers(bool state) {
  torrent::TrackerList tl = m_download.tracker_list();

  for (int i = 0, last = tl.size(); i < last; ++i)
    if (tl.get(i).tracker_type() == torrent::Tracker::TRACKER_UDP)
      if (state)
        tl.get(i).enable();
      else
        tl.get(i).disable();
}