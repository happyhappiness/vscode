void
Manager::try_create_download_expand(const std::string& uri, int flags, command_list_type commands) {
  std::vector<std::string> paths;
  paths.reserve(256);

  path_expand(&paths, uri);

  if (flags & create_tied)
    for (std::vector<std::string>::iterator itr = paths.begin(); itr != paths.end(); )
      if (std::find_if(m_downloadList->begin(), m_downloadList->end(), rak::bind1st(std::ptr_fun(&manager_equal_tied), *itr))
          != m_downloadList->end())
        itr = paths.erase(itr);
      else
        itr++;

  if (!paths.empty())
    for (std::vector<std::string>::iterator itr = paths.begin(); itr != paths.end(); ++itr)
      try_create_download(*itr, flags, commands);

  else
    try_create_download(uri, flags, commands);
}