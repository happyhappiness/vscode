   download_type*       download()                              { return &m_download; }
   const download_type* c_download() const                      { return &m_download; }
 
   file_list_type*       file_list()                            { return m_download.file_list(); }
   const file_list_type* c_file_list() const                    { return m_download.file_list(); }
 
+  peer_list_type*       peer_list()                            { return m_download.peer_list(); }
+  const peer_list_type* c_peer_list() const                    { return m_download.peer_list(); }
+
   torrent::Object*    bencode()                                { return m_download.bencode(); }
-  tracker_list_type*  tracker_list()                           { return &m_trackerList; }
+
+  tracker_list_type*  tracker_list()                           { return m_download.tracker_list(); }
+  uint32_t            tracker_list_size() const                { return m_download.tracker_list()->size(); }
+
+  connection_list_type* connection_list()                      { return m_download.connection_list(); }
+  uint32_t              connection_list_size() const;
 
   const std::string&  message() const                          { return m_message; }
   void                set_message(const std::string& msg)      { m_message = msg; }
 
   uint32_t            chunks_failed() const                    { return m_chunksFailed; }
 
