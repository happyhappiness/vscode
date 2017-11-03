void
Download::bind_keys() {
  m_bindings['1'] = sigc::bind(sigc::mem_fun(this, &Download::receive_max_uploads), -1);
  m_bindings['2'] = sigc::bind(sigc::mem_fun(this, &Download::receive_max_uploads), 1);
  m_bindings['3'] = sigc::bind(sigc::mem_fun(this, &Download::receive_min_peers), -5);
  m_bindings['4'] = sigc::bind(sigc::mem_fun(this, &Download::receive_min_peers), 5);
  m_bindings['5'] = sigc::bind(sigc::mem_fun(this, &Download::receive_max_peers), -5);
  m_bindings['6'] = sigc::bind(sigc::mem_fun(this, &Download::receive_max_peers), 5);
  m_bindings['+'] = sigc::mem_fun(this, &Download::receive_next_priority);
  m_bindings['-'] = sigc::mem_fun(this, &Download::receive_prev_priority);

  m_bindings['t'] = sigc::bind(sigc::mem_fun(m_download->tracker_list(), &torrent::TrackerList::manual_request), false);
  m_bindings['T'] = sigc::bind(sigc::mem_fun(m_download->tracker_list(), &torrent::TrackerList::manual_request), true);
}