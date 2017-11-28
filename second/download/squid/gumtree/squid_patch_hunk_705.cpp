     void stop(const char *context);
 
     /// returns the total time of all ICAP processing intervals
     int processingTime() const;
 
     String rfc931; ///< the username from ident
-#if USE_SSL
+#if USE_OPENSSL
     String ssluser; ///< the username from SSL
 #endif
     LogTags logType; ///< the squid request status (TCP_MISS etc)
 
     String log_uri; ///< the request uri
     size_t req_sz; ///< the request size
