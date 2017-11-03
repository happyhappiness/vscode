void
DownloadList::clear() {
  std::for_each(begin(), end(), std::bind1st(std::mem_fun(&DownloadList::close), this));
  std::for_each(begin(), end(), rak::call_delete<Download>());

  base_type::clear();
}