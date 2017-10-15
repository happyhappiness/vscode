
  void                push_log(const char* msg);
  void                push_log_std(const std::string& msg) { m_logImportant.push_front(msg); m_logComplete.push_front(msg); }

  void                handshake_log(const sockaddr* sa, int msg, int err, const torrent::HashString* hash);

  static const int create_start = 0x1;
  static const int create_tied  = 0x2;
  static const int create_quiet = 0x4;

  typedef std::vector<std::string> command_list_type;

  // Temporary, find a better place for this.
  void                try_create_download(const std::string& uri, int flags, const command_list_type& commands);
  void                try_create_download_expand(const std::string& uri, int flags, command_list_type commands = command_list_type());
