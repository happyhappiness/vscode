
  for (unsigned int y = 1; y < m_canvas->height() && itr != transfers->end(); ++y, ++itr) {
    m_canvas->print(0, y, "%5u [P: %u F: %u]", (*itr)->index(), (*itr)->priority(), (*itr)->failed());

    // Handle window size.
    for (torrent::BlockList::const_iterator bItr = (*itr)->begin(), bLast = (*itr)->end(); bItr != bLast; ++bItr) {
      char id;
      chtype attr = A_NORMAL;

      if (bItr->is_finished()) {
        attr = A_REVERSE;
        id = key_id(bItr->leader()->const_peer_info());
