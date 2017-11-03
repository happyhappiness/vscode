void
DownloadFactory::receive_load() {
  if (m_stream)
    throw torrent::internal_error("DownloadFactory::load() called on an object with m_stream != NULL");

  if (std::strncmp(m_uri.c_str(), "http://", 7) == 0 ||
      std::strncmp(m_uri.c_str(), "https://", 8) == 0 ||
      std::strncmp(m_uri.c_str(), "ftp://", 6) == 0) {
    // Http handling here.
    m_stream = new std::stringstream;
    HttpQueue::iterator itr = m_manager->http_queue()->insert(m_uri, m_stream);

    (*itr)->signal_done().slots().push_front(sigc::mem_fun(*this, &DownloadFactory::receive_loaded));
    (*itr)->signal_failed().slots().push_front(sigc::mem_fun(*this, &DownloadFactory::receive_failed));

    m_variables["tied_to_file"] = (int64_t)false;

  } else {
    std::fstream* stream = new std::fstream(rak::path_expand(m_uri).c_str(), std::ios::in | std::ios::binary);
    m_stream = stream;

    if (stream->is_open())
      receive_loaded();
    else
      receive_failed("Could not open file");
  }
}