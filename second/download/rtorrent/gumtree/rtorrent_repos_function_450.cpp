inline void
DownloadList::check_contains(Download* d) {
#ifdef USE_EXTRA_DEBUG
  if (std::find(begin(), end(), d) == end())
    throw torrent::internal_error("DownloadList::check_contains(...) failed.");
#endif
}