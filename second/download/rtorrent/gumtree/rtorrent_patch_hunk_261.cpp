   void                set_proxy_address(const std::string& addr);
 
   void                shutdown(bool force);
 
   void                push_log(const char* msg);
   void                push_log_std(const std::string& msg) { m_logImportant.push_front(msg); m_logComplete.push_front(msg); }
+  void                push_log_complete(const std::string& msg) { m_logComplete.push_front(msg); }
 
   void                handshake_log(const sockaddr* sa, int msg, int err, const torrent::HashString* hash);
 
   static const int create_start    = 0x1;
   static const int create_tied     = 0x2;
   static const int create_quiet    = 0x4;
