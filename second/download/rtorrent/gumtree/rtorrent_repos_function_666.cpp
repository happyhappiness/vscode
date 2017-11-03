void
WindowDownloadTransferList::redraw() {
  // TODO: Make this depend on tracker signal.
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());
  m_canvas->erase();

  if (m_canvas->height() < 3 || m_canvas->width() < 18)
    return;

  const torrent::TransferList* transfers = m_download->download()->transfer_list();

  m_canvas->print(2, 0, "Transfer list: [Size %i]", transfers->size());

  torrent::TransferList::const_iterator itr = transfers->begin();

  // This is just for testing and the layout and included information
  // is just something i threw in there, someone really should
  // prettify this. (This is a very subtle hint)

  for (unsigned int y = 1; y < m_canvas->height() && itr != transfers->end(); ++y, ++itr) {
    m_canvas->print(0, y, "%5u [P: %u F: %u]", (*itr)->index(), (*itr)->priority(), (*itr)->failed());

    // Handle window size.
    for (torrent::BlockList::const_iterator bItr = (*itr)->begin(), bLast = (*itr)->end(); bItr != bLast; ++bItr) {
      if (m_canvas->get_x() >= m_canvas->width() - 1) {
        if (++y >= m_canvas->height())
          break;

        m_canvas->move(17, y);
      }

      char id;
      chtype attr = A_NORMAL;

      if (bItr->is_finished()) {
        attr = A_REVERSE;
        id = key_id(bItr->leader()->const_peer_info());
        
      } else if (bItr->is_transfering()) {
        attr = A_BOLD;
        id = key_id(bItr->leader()->const_peer_info());

      } else if (bItr->queued()->size() >= 1) {
        id = std::tolower(key_id(bItr->queued()->back()->const_peer_info()));

      } else {
        id = '.';
      }

      if (bItr->size_all() > 1)
        attr |= A_UNDERLINE;

      m_canvas->print_char(attr | id);
    }
  }
}