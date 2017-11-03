void
DownloadList::erase_ptr(Download* download) {
  erase(std::find(begin(), end(), download));
}