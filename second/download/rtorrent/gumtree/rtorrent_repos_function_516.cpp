void
View::clear_filter_on() {
  // Don't clear insert and erase as these are required to keep the
  // View up-to-date with the available downloads.
  std::for_each(m_list->slot_map_begin() + DownloadList::SLOTS_OPEN, m_list->slot_map_end(), rak::bind2nd(std::ptr_fun(&DownloadList::erase_key), "0_view_" + m_name));
}