utils::Directory
DownloadStore::get_formated_entries() {
  if (!is_enabled())
    return utils::Directory();

  utils::Directory d(m_path);

  if (!d.update())
    throw torrent::storage_error("core::DownloadStore::update() could not open directory \"" + m_path + "\"");

  d.erase(std::remove_if(d.begin(), d.end(), std::not1(std::ptr_fun(&DownloadStore::is_correct_format))), d.end());

  return d;
}