void
Download::receive_storage_error(std::string msg) {
  m_message = "Storage error: [" + msg + "]";
}