   curl_off_t recvpersecond; /* receive from peer */
   struct timeval lastsendtime;
   size_t lastsendsize;
   struct timeval lastrecvtime;
   size_t lastrecvsize;
   bool ftp_ssl;
-  char *socks5proxy;
+  bool ftp_ssl_reqd;
+  bool ftp_ssl_control;
+
+  char *socksproxy; /* set to server string */
+  int socksver;     /* set to CURLPROXY_SOCKS* define */
+
   bool tcp_nodelay;
   long req_retry;   /* number of retries */
   long retry_delay; /* delay between retries (in seconds) */
   long retry_maxtime; /* maximum time to keep retrying */
 
-  char *tp_url; /* third party URL */
-  char *tp_user; /* third party userpwd */
-  struct curl_slist *tp_quote;
-  struct curl_slist *tp_postquote;
-  struct curl_slist *tp_prequote;
   char *ftp_account; /* for ACCT */
+  char *ftp_alternative_to_user; /* send command if USER/PASS fails */
+  int ftp_filemethod;
 
   bool ignorecl; /* --ignore-content-length */
+  bool disable_sessionid;
+
+  struct OutStruct *outs;
 };
 
 #define WARN_PREFIX "Warning: "
-#define WARN_TEXTWIDTH (79 - strlen(WARN_PREFIX))
+#define WARN_TEXTWIDTH (79 - (int)strlen(WARN_PREFIX))
 /* produce this text message to the user unless mute was selected */
 static void warnf(struct Configurable *config, const char *fmt, ...)
 {
   if(!(config->conf & CONF_MUTE)) {
     va_list ap;
     int len;
