void operator () (const DownloadList::slot_map::value_type& s) {
    try {
      s.second(m_download);
    } catch (torrent::input_error& e) {
      control->core()->push_log((std::string("Download event action failed: ") + e.what()).c_str());
    }
  }