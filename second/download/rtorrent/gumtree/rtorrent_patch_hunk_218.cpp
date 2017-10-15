 
   std::string         proxy_address() const;
   void                set_proxy_address(const std::string& addr);
 
   void                shutdown(bool force);
 
-  void                push_log(const std::string& msg)    { m_logImportant.push_front(msg); m_logComplete.push_front(msg); }
+  void                push_log(const char* msg);
+  void                push_log_std(const std::string& msg) { m_logImportant.push_front(msg); m_logComplete.push_front(msg); }
 
   void                handshake_log(const sockaddr* sa, int msg, int err, const torrent::HashString* hash);
 
-  // Temporary, find a better place for this.
-  void                try_create_download(const std::string& uri, bool start, bool printLog = true, bool tied = false);
-  void                try_create_download_expand(const std::string& uri, bool start, bool printLog = true, bool tied = false);
+  static const int create_start = 0x1;
+  static const int create_tied  = 0x2;
+  static const int create_quiet = 0x4;
 
-  void                delete_tied(Download* d);
+  typedef std::vector<std::string> command_list_type;
+
+  // Temporary, find a better place for this.
+  void                try_create_download(const std::string& uri, int flags, const command_list_type& commands);
+  void                try_create_download_expand(const std::string& uri, int flags, command_list_type commands = command_list_type());
 
 private:
   void                create_http(const std::string& uri);
   void                create_final(std::istream* s);
 
   void                initialize_bencode(Download* d);
