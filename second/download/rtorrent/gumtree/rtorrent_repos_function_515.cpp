void
View::set_filter_on(int event) {
  if (event == DownloadList::SLOTS_INSERT || event == DownloadList::SLOTS_ERASE || event >= DownloadList::SLOTS_MAX_SIZE)
    throw torrent::internal_error("View::filter_on(...) invalid event.");

  m_list->slots(event)["0_view_" + m_name]  = sigc::bind(sigc::mem_fun(this, &View::received), event);
}