void
Manager::receive_hashing_changed() {
  bool foundHashing = std::find_if(m_hashingView->begin_visible(), m_hashingView->end_visible(),
                                   std::mem_fun(&Download::is_hash_checking)) != m_hashingView->end_visible();
  
  // Try quick hashing all those with hashing == initial, set them to
  // something else when failed.
  for (View::iterator itr = m_hashingView->begin_visible(), last = m_hashingView->end_visible(); itr != last; ++itr) {
    if ((*itr)->is_hash_checked())
      throw torrent::internal_error("core::Manager::receive_hashing_changed() (*itr)->is_hash_checked().");
  
    if ((*itr)->is_hash_checking() || (*itr)->is_hash_failed())
      continue;

    bool tryQuick =
      rpc::call_command_d_value("d.get_hashing", *itr) == Download::variable_hashing_initial &&
      (*itr)->download()->file_list()->bitfield()->empty();

    if (!tryQuick && foundHashing)
      continue;

    try {
      m_downloadList->open_throw(*itr);

      // Since the bitfield is allocated on loading of resume load or
      // hash start, and unallocated on close, we know that if it it
      // not empty then we have already loaded any existing resume
      // data.
      if ((*itr)->download()->file_list()->bitfield()->empty())
        torrent::resume_load_progress(*(*itr)->download(), (*itr)->download()->bencode()->get_key("libtorrent_resume"));

      if (tryQuick) {
        if ((*itr)->download()->hash_check(true))
          continue;

        (*itr)->download()->hash_stop();

        if (foundHashing) {
          rpc::call_command_d_set_value("d.set_hashing", *itr, Download::variable_hashing_rehash);
          continue;
        }
      }

      (*itr)->download()->hash_check(false);
      foundHashing = true;

    } catch (torrent::local_error& e) {
      if (tryQuick) {
        // Make sure we don't repeat the quick hashing.
        rpc::call_command_d_set_value("d.set_hashing", *itr, Download::variable_hashing_rehash);

      } else {
        (*itr)->set_hash_failed(true);
        push_log(e.what());
      }
    }
  }
}