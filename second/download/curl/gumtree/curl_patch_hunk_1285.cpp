   {"SSL",            CURL_VERSION_SSL},
   {"libz",           CURL_VERSION_LIBZ},
   {"CharConv",       CURL_VERSION_CONV},
   {"TLS-SRP",        CURL_VERSION_TLSAUTH_SRP},
   {"HTTP2",          CURL_VERSION_HTTP2},
   {"UnixSockets",    CURL_VERSION_UNIX_SOCKETS},
-  {"HTTPS-proxy",    CURL_VERSION_HTTPS_PROXY}
+  {"HTTPS-proxy",    CURL_VERSION_HTTPS_PROXY},
+  {"MultiSSL",       CURL_VERSION_MULTI_SSL}
 };
 
 void tool_help(void)
 {
   int i;
   puts("Usage: curl [options...] <url>");
