    throw e;
  }
}

void
Manager::receive_http_failed(std::string msg) {
  m_logImportant.push_front("Http download error: \"" + msg + "\"");
  m_logComplete.push_front("Http download error: \"" + msg + "\"");
}

void
Manager::try_create_download(const std::string& uri, int flags, const command_list_type& commands) {
  // If the path was attempted loaded before, skip it.
  if ((flags & create_tied) &&
