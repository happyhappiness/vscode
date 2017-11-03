DownloadList::iterator
DownloadList::find_hex(const char* hash) {
  torrent::HashString key;

  for (torrent::HashString::iterator itr = key.begin(), last = key.end(); itr != last; itr++, hash += 2)
    *itr = (rak::hexchar_to_value(*hash) << 4) + rak::hexchar_to_value(*(hash + 1));

  return std::find_if(begin(), end(), rak::equal(key, rak::on(std::mem_fun(&Download::download), std::mem_fun(&torrent::Download::info_hash))));
}