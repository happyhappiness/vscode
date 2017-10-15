
  m_download.bencode()->get_key("rtorrent").insert_key("throttle_name", throttleName);
}

void
Download::set_root_directory(const std::string& path) {
  torrent::FileList* fileList = m_download.file_list();

  control->core()->download_list()->close_directly(this);
  fileList->set_root_dir(rak::path_expand(path));

  bencode()->get_key("rtorrent").insert_key("directory", path);
}

}
