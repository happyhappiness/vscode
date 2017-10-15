  std::string         proxy_address() const;
  void                set_proxy_address(const std::string& addr);

  void                shutdown(bool force);

  void                push_log(const char* msg);
  void                push_log_std(const std::string& msg) { m_log_important->lock_and_push_log(msg.c_str(), msg.size(), 0); m_log_complete->lock_and_push_log(msg.c_str(), msg.size(), 0); }
  void                push_log_complete(const std::string& msg) { m_log_complete->lock_and_push_log(msg.c_str(), msg.size(), 0); }

  void                handshake_log(const sockaddr* sa, int msg, int err, const torrent::HashString* hash);

  static const int create_start    = 0x1;
  static const int create_tied     = 0x2;
  static const int create_quiet    = 0x4;
