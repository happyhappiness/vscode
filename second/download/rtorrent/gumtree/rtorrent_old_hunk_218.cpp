
  std::string         proxy_address() const;
  void                set_proxy_address(const std::string& addr);

  void                shutdown(bool force);

  void                push_log(const std::string& msg)    { m_logImportant.push_front(msg); m_logComplete.push_front(msg); }

  void                handshake_log(const sockaddr* sa, int msg, int err, const torrent::HashString* hash);

  // Temporary, find a better place for this.
  void                try_create_download(const std::string& uri, bool start, bool printLog = true, bool tied = false);
  void                try_create_download_expand(const std::string& uri, bool start, bool printLog = true, bool tied = false);

  void                delete_tied(Download* d);

private:
  void                create_http(const std::string& uri);
  void                create_final(std::istream* s);

  void                initialize_bencode(Download* d);
