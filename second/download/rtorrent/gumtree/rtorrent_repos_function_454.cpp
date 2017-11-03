DownloadList::iterator
DownloadList::find(const torrent::HashString& hash) {
  return std::find_if(begin(), end(), rak::equal(hash, rak::on(std::mem_fun(&Download::download), std::mem_fun(&torrent::Download::info_hash))));
}