std::string
DownloadStore::create_filename(Download* d) {
  return m_path + rak::transform_hex(d->download()->info_hash().begin(), d->download()->info_hash().end()) + ".torrent";
}