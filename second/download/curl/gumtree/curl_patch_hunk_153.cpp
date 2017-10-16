   _lseeki64(fd, curr, SEEK_SET);
   return rc;
 }
 #define ftruncate(fd,where) ftruncate64(fd,where)
 #endif
 
+typedef enum {
+    TRACE_BIN,   /* tcpdump inspired look */
+    TRACE_ASCII, /* like *BIN but without the hex output */
+    TRACE_PLAIN  /* -v/--verbose type */
+} trace;
+
+struct Configurable {
+  bool remote_time;
+  char *random_file;
+  char *egd_file;
+  char *useragent;
+  char *cookie;     /* single line with specified cookies */
+  char *cookiejar;  /* write to this file */
+  char *cookiefile; /* read from this file */
+  bool cookiesession; /* new session? */
+  bool encoding;    /* Accept-Encoding please */
+  long authtype;    /* auth bitmask */
+  bool use_resume;
+  bool resume_from_current;
+  bool disable_epsv;
+  bool disable_eprt;
+  curl_off_t resume_from;
+  char *postfields;
+  long postfieldsize;
+  char *referer;
+  long timeout;
+  long connecttimeout;
+  long maxredirs;
+  curl_off_t max_filesize;
+  char *headerfile;
+  char *ftpport;
+  char *iface;
+  unsigned short porttouse;
+  char *range;
+  long low_speed_limit;
+  long low_speed_time;
+  bool showerror;
+  char *userpwd;
+  char *proxyuserpwd;
+  char *proxy;
+  bool proxytunnel;
+  long conf;
+  struct getout *url_list; /* point to the first node */
+  struct getout *url_last; /* point to the last/current node */
+  struct getout *url_get;  /* point to the node to fill in URL */
+  struct getout *url_out;  /* point to the node to fill in outfile */
+  char *cipher_list;
+  char *cert;
+  char *cert_type;
+  char *cacert;
+  char *capath;
+  char *key;
+  char *key_type;
+  char *key_passwd;
+  char *engine;
+  bool list_engines;
+  bool crlf;
+  char *customrequest;
+  char *krb4level;
+  char *trace_dump; /* file to dump the network trace to, or NULL */
+  FILE *trace_stream;
+  bool trace_fopened;
+  trace tracetype;
+  bool tracetime; /* include timestamp? */
+  long httpversion;
+  bool progressmode;
+  bool nobuffer;
+  bool globoff;
+  bool use_httpget;
+  bool insecure_ok; /* set TRUE to allow insecure SSL connects */
+  bool create_dirs;
+  bool ftp_create_dirs;
+  bool ftp_skip_ip;
+  bool proxyntlm;
+  bool proxydigest;
+  bool proxybasic;
+  bool proxyanyauth;
+  char *writeout; /* %-styled format string to output */
+  bool writeenv; /* write results to environment, if available */
+  FILE *errors; /* if stderr redirect is requested */
+  bool errors_fopened;
+  struct curl_slist *quote;
+  struct curl_slist *postquote;
+  struct curl_slist *prequote;
+  long ssl_version;
+  long ip_version;
+  curl_TimeCond timecond;
+  time_t condtime;
+  struct curl_slist *headers;
+  struct curl_httppost *httppost;
+  struct curl_httppost *last_post;
+  struct curl_slist *telnet_options;
+  HttpReq httpreq;
+
+  /* for bandwidth limiting features: */
+  curl_off_t sendpersecond; /* send to peer */
+  curl_off_t recvpersecond; /* receive from peer */
+  struct timeval lastsendtime;
+  size_t lastsendsize;
+  struct timeval lastrecvtime;
+  size_t lastrecvsize;
+  bool ftp_ssl;
+  char *socks5proxy;
+  bool tcp_nodelay;
+  long req_retry;   /* number of retries */
+  long retry_delay; /* delay between retries (in seconds) */
+  long retry_maxtime; /* maximum time to keep retrying */
+
+  char *tp_url; /* third party URL */
+  char *tp_user; /* third party userpwd */
+  struct curl_slist *tp_quote;
+  struct curl_slist *tp_postquote;
+  struct curl_slist *tp_prequote;
+  char *ftp_account; /* for ACCT */
+
+  bool ignorecl; /* --ignore-content-length */
+};
+
+#define WARN_PREFIX "Warning: "
+#define WARN_TEXTWIDTH (79 - strlen(WARN_PREFIX))
+/* produce this text message to the user unless mute was selected */
+static void warnf(struct Configurable *config, const char *fmt, ...)
+{
+  if(!(config->conf & CONF_MUTE)) {
+    va_list ap;
+    int len;
+    char *ptr;
+    char print_buffer[256];
+
+    va_start(ap, fmt);
+    va_start(ap, fmt);
+    len = vsnprintf(print_buffer, sizeof(print_buffer), fmt, ap);
+    va_end(ap);
+
+    ptr = print_buffer;
+    while(len > 0) {
+      fputs(WARN_PREFIX, config->errors);
+
+      if(len > (int)WARN_TEXTWIDTH) {
+        int cut = WARN_TEXTWIDTH-1;
+
+        while(!isspace((int)ptr[cut]) && cut) {
+          cut--;
+        }
+
+        fwrite(ptr, cut + 1, 1, config->errors);
+        fputs("\n", config->errors);
+        ptr += cut+1; /* skip the space too */
+        len -= cut;
+      }
+      else {
+        fputs(ptr, config->errors);
+        len = 0;
+      }
+    }
+  }
+}
+
 /*
  * This is the main global constructor for the app. Call this before
  * _any_ libcurl usage. If this fails, *NO* libcurl functions may be
  * used, or havoc may be the result.
  */
 static CURLcode main_init(void)
