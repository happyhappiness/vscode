void
Manager::shutdown(bool force) {
  if (!force)
    std::for_each(m_downloadList->begin(), m_downloadList->end(), std::bind1st(std::mem_fun(&DownloadList::pause), m_downloadList));
  else
    std::for_each(m_downloadList->begin(), m_downloadList->end(), std::bind1st(std::mem_fun(&DownloadList::close_quick), m_downloadList));
}