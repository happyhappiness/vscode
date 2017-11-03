void
DownloadList::session_save() {
  std::for_each(begin(), end(), std::bind1st(std::mem_fun(&DownloadStore::save), control->core()->download_store()));
}