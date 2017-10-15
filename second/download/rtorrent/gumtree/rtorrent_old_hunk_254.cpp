  download_type*       download()                              { return &m_download; }
  const download_type* c_download() const                      { return &m_download; }

  file_list_type*       file_list()                            { return m_download.file_list(); }
  const file_list_type* c_file_list() const                    { return m_download.file_list(); }

  torrent::Object*    bencode()                                { return m_download.bencode(); }
  tracker_list_type*  tracker_list()                           { return &m_trackerList; }

  const std::string&  message() const                          { return m_message; }
  void                set_message(const std::string& msg)      { m_message = msg; }

  uint32_t            chunks_failed() const                    { return m_chunksFailed; }

