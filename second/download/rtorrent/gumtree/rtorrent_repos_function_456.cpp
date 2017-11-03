Download*
DownloadList::find_hex_ptr(const char* hash) {
  iterator itr = find_hex(hash);

  return itr != end() ? *itr : NULL;
}