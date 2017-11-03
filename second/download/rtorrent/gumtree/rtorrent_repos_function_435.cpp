void
Download::set_root_directory(const std::string& path) {
  torrent::FileList* fileList = m_download.file_list();

  if (path.empty()) {
    fileList->set_root_dir("./" + (fileList->is_multi_file() ? m_download.name() : std::string()));

  } else {
    std::string fullPath = rak::path_expand(path);

    fileList->set_root_dir(fullPath +
                           (*fullPath.rbegin() != '/' ? "/" : "") +
                           (fileList->is_multi_file() ? m_download.name() : std::string()));
  }

  bencode()->get_key("rtorrent").insert_key("directory", path);
}