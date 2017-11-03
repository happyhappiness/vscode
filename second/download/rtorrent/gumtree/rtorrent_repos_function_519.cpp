void
View::received(core::Download* download, int event) {
  iterator itr = std::find(base_type::begin(), base_type::end(), download);

  switch (event) {
  case DownloadList::SLOTS_INSERT:
  
    if (itr != base_type::end())
      throw torrent::internal_error("View::received(..., SLOTS_INSERT) already inserted.");

    if (view_downloads_filter(m_filter)(download))
      insert_visible(download);
    else
      base_type::insert(end_filtered(), download);

    if (m_focus > m_size)
      throw torrent::internal_error("View::received(...) m_focus > m_size.");

    break;

  case DownloadList::SLOTS_ERASE:
    erase(itr);
    break;

  default:
    if (itr == end_filtered())
      throw torrent::internal_error("View::received(..., SLOTS_*) could not find download.");

    if (view_downloads_filter(m_filter)(download)) {
      
      // Erase even if it is in visible so that the download is
      // re-sorted.
      erase(itr);
      insert_visible(download);

    } else {

      if (itr >= begin_filtered())
        return;

      erase(itr);
      base_type::push_back(download);
    }

    break;
  }

  m_signalChanged.emit();
}