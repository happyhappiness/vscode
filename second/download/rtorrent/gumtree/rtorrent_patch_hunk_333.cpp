   connection_list_type* connection_list()                      { return m_download.connection_list(); }
   uint32_t              connection_list_size() const;
 
   const std::string&  message() const                          { return m_message; }
   void                set_message(const std::string& msg)      { m_message = msg; }
 
-  uint32_t            chunks_failed() const                    { return m_chunksFailed; }
-
   void                enable_udp_trackers(bool state);
 
   uint32_t            priority();
   void                set_priority(uint32_t p);
 
   uint32_t            resume_flags()                           { return m_resumeFlags; }
