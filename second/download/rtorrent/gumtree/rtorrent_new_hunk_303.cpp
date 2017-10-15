
  torrent::Object*    bencode()                                { return m_download.bencode(); }

  tracker_list_type*  tracker_list()                           { return m_download.tracker_list(); }
  uint32_t            tracker_list_size() const                { return m_download.tracker_list()->size(); }

  tracker_controller_type* tracker_controller()                { return m_download.tracker_controller(); }

  connection_list_type* connection_list()                      { return m_download.connection_list(); }
  uint32_t              connection_list_size() const;

  const std::string&  message() const                          { return m_message; }
  void                set_message(const std::string& msg)      { m_message = msg; }

