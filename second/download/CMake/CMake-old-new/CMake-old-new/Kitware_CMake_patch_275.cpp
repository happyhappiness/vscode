@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -77,9 +77,7 @@
 #include "warnless.h"
 #include "http_proxy.h"
 #include "non-ascii.h"
-
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
+#include "curl_printf.h"
 
 #include "curl_memory.h"
 /* The last #include file should be: */
@@ -157,7 +155,7 @@ static CURLcode ftp_dophase_done(struct connectdata *conn,
                                  bool connected);
 
 /* easy-to-use macro: */
-#define PPSENDF(x,y,z)  if((result = Curl_pp_sendf(x,y,z)) != CURLE_OK) \
+#define PPSENDF(x,y,z)  if((result = Curl_pp_sendf(x,y,z)))     \
                               return result
 
 
@@ -285,19 +283,17 @@ static void freedirs(struct ftp_conn *ftpc)
   int i;
   if(ftpc->dirs) {
     for(i=0; i < ftpc->dirdepth; i++) {
-      if(ftpc->dirs[i]) {
-        free(ftpc->dirs[i]);
-        ftpc->dirs[i]=NULL;
-      }
+      free(ftpc->dirs[i]);
+      ftpc->dirs[i]=NULL;
     }
     free(ftpc->dirs);
     ftpc->dirs = NULL;
     ftpc->dirdepth = 0;
   }
-  if(ftpc->file) {
-    free(ftpc->file);
-    ftpc->file = NULL;
-  }
+  Curl_safefree(ftpc->file);
+
+  /* no longer of any use */
+  Curl_safefree(ftpc->newhost);
 }
 
 /* Returns non-zero if the given string contains CR (\r) or LF (\n),
@@ -346,7 +342,7 @@ static CURLcode AcceptServerConnect(struct connectdata *conn)
   infof(data, "Connection accepted from server\n");
 
   conn->sock[SECONDARYSOCKET] = s;
-  curlx_nonblock(s, TRUE); /* enable non-blocking */
+  (void)curlx_nonblock(s, TRUE); /* enable non-blocking */
   conn->sock_accepted[SECONDARYSOCKET] = TRUE;
 
   if(data->set.fsockopt) {
@@ -541,7 +537,7 @@ static CURLcode AllowServerConnect(struct connectdata *conn, bool *connected)
 {
   struct SessionHandle *data = conn->data;
   long timeout_ms;
-  CURLcode ret = CURLE_OK;
+  CURLcode result = CURLE_OK;
 
   *connected = FALSE;
   infof(data, "Preparing for accepting server on data port\n");
@@ -557,30 +553,30 @@ static CURLcode AllowServerConnect(struct connectdata *conn, bool *connected)
   }
 
   /* see if the connection request is already here */
-  ret = ReceivedServerConnect(conn, connected);
-  if(ret)
-    return ret;
+  result = ReceivedServerConnect(conn, connected);
+  if(result)
+    return result;
 
   if(*connected) {
-    ret = AcceptServerConnect(conn);
-    if(ret)
-      return ret;
+    result = AcceptServerConnect(conn);
+    if(result)
+      return result;
 
-    ret = InitiateTransfer(conn);
-    if(ret)
-      return ret;
+    result = InitiateTransfer(conn);
+    if(result)
+      return result;
   }
   else {
     /* Add timeout to multi handle and break out of the loop */
-    if(ret == CURLE_OK && *connected == FALSE) {
+    if(!result && *connected == FALSE) {
       if(data->set.accepttimeout > 0)
         Curl_expire(data, data->set.accepttimeout);
       else
         Curl_expire(data, DEFAULT_ACCEPT_TIMEOUT);
     }
   }
 
-  return ret;
+  return result;
 }
 
 /* macro to check for a three-digit ftp status code at the start of the
@@ -821,12 +817,19 @@ static void _state(struct connectdata *conn,
   )
 {
   struct ftp_conn *ftpc = &conn->proto.ftpc;
-#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
+
+#if defined(DEBUGBUILD)
+
+#if defined(CURL_DISABLE_VERBOSE_STRINGS)
+  (void) lineno;
+#else
   if(ftpc->state != newstate)
     infof(conn->data, "FTP %p (line %d) state change from %s to %s\n",
           (void *)ftpc, lineno, ftp_state_names[ftpc->state],
           ftp_state_names[newstate]);
 #endif
+#endif
+
   ftpc->state = newstate;
 }
 
@@ -1072,8 +1075,9 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
 
     if(*addr != '\0') {
       /* attempt to get the address of the given interface name */
-      switch(Curl_if2ip(conn->ip_addr->ai_family, conn->scope, addr,
-                     hbuf, sizeof(hbuf))) {
+      switch(Curl_if2ip(conn->ip_addr->ai_family,
+                        Curl_ipv6_scope(conn->ip_addr->ai_addr),
+                        conn->scope_id, addr, hbuf, sizeof(hbuf))) {
         case IF2IP_NOT_FOUND:
           /* not an interface, use the given string as host name instead */
           host = addr;
@@ -1097,7 +1101,7 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
     if(getsockname(conn->sock[FIRSTSOCKET], sa, &sslen)) {
       failf(data, "getsockname() failed: %s",
           Curl_strerror(conn, SOCKERRNO) );
-      Curl_safefree(addr);
+      free(addr);
       return CURLE_FTP_PORT_FAILED;
     }
     switch(sa->sa_family) {
@@ -1129,11 +1133,11 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
 
   if(res == NULL) {
     failf(data, "failed to resolve the address provided to PORT: %s", host);
-    Curl_safefree(addr);
+    free(addr);
     return CURLE_FTP_PORT_FAILED;
   }
 
-  Curl_safefree(addr);
+  free(addr);
   host = NULL;
 
   /* step 2, create a socket for the requested address */
@@ -1246,10 +1250,10 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
       continue;
 
     if((PORT == fcmd) && sa->sa_family != AF_INET)
-      /* PORT is ipv4 only */
+      /* PORT is IPv4 only */
       continue;
 
-    switch (sa->sa_family) {
+    switch(sa->sa_family) {
     case AF_INET:
       port = ntohs(sa4->sin_port);
       break;
@@ -1487,13 +1491,13 @@ static CURLcode ftp_state_list(struct connectdata *conn)
      The other ftp_filemethods will CWD into dir/dir/ first and
      then just do LIST (in that case: nothing to do here)
   */
-  char *cmd,*lstArg,*slashPos;
+  char *cmd, *lstArg, *slashPos;
 
   lstArg = NULL;
   if((data->set.ftp_filemethod == FTPFILE_NOCWD) &&
      data->state.path &&
      data->state.path[0] &&
-     strchr(data->state.path,'/')) {
+     strchr(data->state.path, '/')) {
 
     lstArg = strdup(data->state.path);
     if(!lstArg)
@@ -1503,7 +1507,7 @@ static CURLcode ftp_state_list(struct connectdata *conn)
     if(lstArg[strlen(lstArg) - 1] != '/')  {
 
       /* chop off the file part if format is dir/dir/file */
-      slashPos = strrchr(lstArg,'/');
+      slashPos = strrchr(lstArg, '/');
       if(slashPos)
         *(slashPos+1) = '\0';
     }
@@ -1517,19 +1521,16 @@ static CURLcode ftp_state_list(struct connectdata *conn)
                  lstArg? lstArg: "" );
 
   if(!cmd) {
-    if(lstArg)
-      free(lstArg);
+    free(lstArg);
     return CURLE_OUT_OF_MEMORY;
   }
 
   result = Curl_pp_sendf(&conn->proto.ftpc.pp, "%s", cmd);
 
-  if(lstArg)
-    free(lstArg);
-
+  free(lstArg);
   free(cmd);
 
-  if(result != CURLE_OK)
+  if(result)
     return result;
 
   state(conn, FTP_LIST);
@@ -1669,8 +1670,8 @@ static CURLcode ftp_state_ul_setup(struct connectdata *conn,
             BUFSIZE : curlx_sotouz(data->state.resume_from - passed);
 
           size_t actuallyread =
-            conn->fread_func(data->state.buffer, 1, readthisamountnow,
-                             conn->fread_in);
+            data->set.fread_func(data->state.buffer, 1, readthisamountnow,
+                                 data->set.in);
 
           passed += actuallyread;
           if((actuallyread == 0) || (actuallyread > readthisamountnow)) {
@@ -1807,6 +1808,13 @@ static CURLcode ftp_state_quote(struct connectdata *conn,
 static CURLcode ftp_epsv_disable(struct connectdata *conn)
 {
   CURLcode result = CURLE_OK;
+
+  if(conn->bits.ipv6) {
+    /* We can't disable EPSV when doing IPv6, so this is instead a fail */
+    failf(conn->data, "Failed EPSV attempt, exiting\n");
+    return CURLE_FTP_WEIRD_SERVER_REPLY;
+  }
+
   infof(conn->data, "Failed EPSV attempt. Disabling EPSV\n");
   /* disable it for next transfer */
   conn->bits.ftp_use_epsv = FALSE;
@@ -1828,9 +1836,15 @@ static CURLcode proxy_magic(struct connectdata *conn,
                             bool *magicdone)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data=conn->data;
+  struct SessionHandle *data = conn->data;
+
+#if defined(CURL_DISABLE_PROXY)
+  (void) newhost;
+  (void) newport;
+#endif
 
   *magicdone = FALSE;
+
   switch(conn->proxytype) {
   case CURLPROXY_SOCKS5:
   case CURLPROXY_SOCKS5_HOSTNAME:
@@ -1873,7 +1887,7 @@ static CURLcode proxy_magic(struct connectdata *conn,
     memset(&http_proxy, 0, sizeof(http_proxy));
     data->req.protop = &http_proxy;
 
-    result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, newhost, newport);
+    result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, newhost, newport, TRUE);
 
     data->req.protop = ftp_save;
 
@@ -1888,9 +1902,26 @@ static CURLcode proxy_magic(struct connectdata *conn,
     else
       *magicdone = TRUE;
   }
+
   return result;
 }
 
+static char *control_address(struct connectdata *conn)
+{
+  /* Returns the control connection IP address.
+     If a proxy tunnel is used, returns the original host name instead, because
+     the effective control connection address is the proxy address,
+     not the ftp host. */
+  if(conn->bits.tunnel_proxy ||
+     conn->proxytype == CURLPROXY_SOCKS5 ||
+     conn->proxytype == CURLPROXY_SOCKS5_HOSTNAME ||
+     conn->proxytype == CURLPROXY_SOCKS4 ||
+     conn->proxytype == CURLPROXY_SOCKS4A)
+    return conn->host.name;
+
+  return conn->ip_addr_str;
+}
+
 static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
                                     int ftpcode)
 {
@@ -1902,6 +1933,9 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
   unsigned short connectport; /* the local port connect() should use! */
   char *str=&data->state.buffer[4];  /* start on the first letter */
 
+  /* if we come here again, make sure the former name is cleared */
+  Curl_safefree(ftpc->newhost);
+
   if((ftpc->count1 == 0) &&
      (ftpcode == 229)) {
     /* positive EPSV response */
@@ -1910,12 +1944,12 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
       unsigned int num;
       char separator[4];
       ptr++;
-      if(5  == sscanf(ptr, "%c%c%c%u%c",
-                      &separator[0],
-                      &separator[1],
-                      &separator[2],
-                      &num,
-                      &separator[3])) {
+      if(5 == sscanf(ptr, "%c%c%c%u%c",
+                     &separator[0],
+                     &separator[1],
+                     &separator[2],
+                     &num,
+                     &separator[3])) {
         const char sep1 = separator[0];
         int i;
 
@@ -1933,19 +1967,9 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
         }
         if(ptr) {
           ftpc->newport = (unsigned short)(num & 0xffff);
-
-          if(conn->bits.tunnel_proxy ||
-             conn->proxytype == CURLPROXY_SOCKS5 ||
-             conn->proxytype == CURLPROXY_SOCKS5_HOSTNAME ||
-             conn->proxytype == CURLPROXY_SOCKS4 ||
-             conn->proxytype == CURLPROXY_SOCKS4A)
-            /* proxy tunnel -> use other host info because ip_addr_str is the
-               proxy address not the ftp host */
-            snprintf(ftpc->newhost, sizeof(ftpc->newhost), "%s",
-                     conn->host.name);
-          else
-            /* use the same IP we are already connected to */
-            snprintf(ftpc->newhost, NEWHOST_BUFSIZE, "%s", conn->ip_addr_str);
+          ftpc->newhost = strdup(control_address(conn));
+          if(!ftpc->newhost)
+            return CURLE_OUT_OF_MEMORY;
         }
       }
       else
@@ -1973,8 +1997,8 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
      */
     while(*str) {
       if(6 == sscanf(str, "%d,%d,%d,%d,%d,%d",
-                      &ip[0], &ip[1], &ip[2], &ip[3],
-                      &port[0], &port[1]))
+                     &ip[0], &ip[1], &ip[2], &ip[3],
+                     &port[0], &port[1]))
         break;
       str++;
     }
@@ -1986,26 +2010,19 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
 
     /* we got OK from server */
     if(data->set.ftp_skip_ip) {
-      /* told to ignore the remotely given IP but instead use the one we used
+      /* told to ignore the remotely given IP but instead use the host we used
          for the control connection */
-      infof(data, "Skips %d.%d.%d.%d for data connection, uses %s instead\n",
+      infof(data, "Skip %d.%d.%d.%d for data connection, re-use %s instead\n",
             ip[0], ip[1], ip[2], ip[3],
-            conn->ip_addr_str);
-      if(conn->bits.tunnel_proxy ||
-         conn->proxytype == CURLPROXY_SOCKS5 ||
-         conn->proxytype == CURLPROXY_SOCKS5_HOSTNAME ||
-         conn->proxytype == CURLPROXY_SOCKS4 ||
-         conn->proxytype == CURLPROXY_SOCKS4A)
-        /* proxy tunnel -> use other host info because ip_addr_str is the
-           proxy address not the ftp host */
-        snprintf(ftpc->newhost, sizeof(ftpc->newhost), "%s", conn->host.name);
-      else
-        snprintf(ftpc->newhost, sizeof(ftpc->newhost), "%s",
-                 conn->ip_addr_str);
+            conn->host.name);
+      ftpc->newhost = strdup(control_address(conn));
     }
     else
-      snprintf(ftpc->newhost, sizeof(ftpc->newhost),
-               "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
+      ftpc->newhost = aprintf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
+
+    if(!ftpc->newhost)
+      return CURLE_OUT_OF_MEMORY;
+
     ftpc->newport = (unsigned short)(((port[0]<<8) + port[1]) & 0xffff);
   }
   else if(ftpc->count1 == 0) {
@@ -2056,9 +2073,8 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
   conn->bits.tcpconnect[SECONDARYSOCKET] = FALSE;
   result = Curl_connecthost(conn, addr);
 
-  Curl_resolv_unlock(data, addr); /* we're done using this address */
-
   if(result) {
+    Curl_resolv_unlock(data, addr); /* we're done using this address */
     if(ftpc->count1 == 0 && ftpcode == 229)
       return ftp_epsv_disable(conn);
 
@@ -2074,8 +2090,9 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
 
   if(data->set.verbose)
     /* this just dumps information about this second connection */
-    ftp_pasv_verbose(conn, conn->ip_addr, ftpc->newhost, connectport);
+    ftp_pasv_verbose(conn, addr->addr, ftpc->newhost, connectport);
 
+  Curl_resolv_unlock(data, addr); /* we're done using this address */
   conn->bits.do_more = TRUE;
   state(conn, FTP_STOP); /* this phase is completed */
 
@@ -2090,7 +2107,9 @@ static CURLcode ftp_state_port_resp(struct connectdata *conn,
   ftpport fcmd = (ftpport)ftpc->count1;
   CURLcode result = CURLE_OK;
 
-  if(ftpcode != 200) {
+  /* The FTP spec tells a positive response should have code 200.
+     Be more permissive here to tolerate deviant servers. */
+  if(ftpcode / 100 != 2) {
     /* the command failed */
 
     if(EPRT == fcmd) {
@@ -2714,7 +2733,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
            set a valid level */
         Curl_sec_request_prot(conn, data->set.str[STRING_KRB_LEVEL]);
 
-        if(Curl_sec_login(conn) != CURLE_OK)
+        if(Curl_sec_login(conn))
           infof(data, "Logging in with password in cleartext!\n");
         else
           infof(data, "Authentication successful\n");
@@ -2765,7 +2784,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
       if((ftpcode == 234) || (ftpcode == 334)) {
         /* Curl_ssl_connect is BLOCKING */
         result = Curl_ssl_connect(conn, FIRSTSOCKET);
-        if(CURLE_OK == result) {
+        if(!result) {
           conn->ssl[SECONDARYSOCKET].use = FALSE; /* clear-text data */
           result = ftp_state_user(conn);
         }
@@ -2907,7 +2926,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
           if(!ftpc->server_os && dir[0] != '/') {
 
             result = Curl_pp_sendf(&ftpc->pp, "%s", "SYST");
-            if(result != CURLE_OK) {
+            if(result) {
               free(dir);
               return result;
             }
@@ -2960,7 +2979,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
         if(strequal(os, "OS/400")) {
           /* Force OS400 name format 1. */
           result = Curl_pp_sendf(&ftpc->pp, "%s", "SITE NAMEFMT 1");
-          if(result != CURLE_OK) {
+          if(result) {
             free(os);
             return result;
           }
@@ -3254,8 +3273,7 @@ static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
   }
 
   /* now store a copy of the directory we are in */
-  if(ftpc->prevpath)
-    free(ftpc->prevpath);
+  free(ftpc->prevpath);
 
   if(data->set.wildcardmatch) {
     if(data->set.chunk_end && ftpc->file) {
@@ -3304,7 +3322,7 @@ static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
   /* shut down the socket to inform the server we're done */
 
 #ifdef _WIN32_WCE
-  shutdown(conn->sock[SECONDARYSOCKET],2);  /* SD_BOTH */
+  shutdown(conn->sock[SECONDARYSOCKET], 2);  /* SD_BOTH */
 #endif
 
   if(conn->sock[SECONDARYSOCKET] != CURL_SOCKET_BAD) {
@@ -3627,7 +3645,7 @@ static CURLcode ftp_do_more(struct connectdata *conn, int *completep)
     if(conn->tunnel_state[SECONDARYSOCKET] == TUNNEL_CONNECT) {
       /* As we're in TUNNEL_CONNECT state now, we know the proxy name and port
          aren't used so we blank their arguments. TODO: make this nicer */
-      result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, NULL, 0);
+      result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, NULL, 0, FALSE);
 
       return result;
     }
@@ -3736,7 +3754,7 @@ static CURLcode ftp_do_more(struct connectdata *conn, int *completep)
     return result;
   }
 
-  if((result == CURLE_OK) && (ftp->transfer != FTPTRANSFER_BODY))
+  if(!result && (ftp->transfer != FTPTRANSFER_BODY))
     /* no data to transfer. FIX: it feels like a kludge to have this here
        too! */
     Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
@@ -3802,24 +3820,24 @@ static void wc_data_dtor(void *ptr)
   struct ftp_wc_tmpdata *tmp = ptr;
   if(tmp)
     Curl_ftp_parselist_data_free(&tmp->parser);
-  Curl_safefree(tmp);
+  free(tmp);
 }
 
 static CURLcode init_wc_data(struct connectdata *conn)
 {
   char *last_slash;
   char *path = conn->data->state.path;
   struct WildcardData *wildcard = &(conn->data->wildcard);
-  CURLcode ret = CURLE_OK;
+  CURLcode result = CURLE_OK;
   struct ftp_wc_tmpdata *ftp_tmp;
 
   last_slash = strrchr(conn->data->state.path, '/');
   if(last_slash) {
     last_slash++;
     if(last_slash[0] == '\0') {
       wildcard->state = CURLWC_CLEAN;
-      ret = ftp_parse_url_path(conn);
-      return ret;
+      result = ftp_parse_url_path(conn);
+      return result;
     }
     else {
       wildcard->pattern = strdup(last_slash);
@@ -3837,8 +3855,8 @@ static CURLcode init_wc_data(struct connectdata *conn)
     }
     else { /* only list */
       wildcard->state = CURLWC_CLEAN;
-      ret = ftp_parse_url_path(conn);
-      return ret;
+      result = ftp_parse_url_path(conn);
+      return result;
     }
   }
 
@@ -3856,7 +3874,7 @@ static CURLcode init_wc_data(struct connectdata *conn)
   ftp_tmp->parser = Curl_ftp_parselist_data_alloc();
   if(!ftp_tmp->parser) {
     Curl_safefree(wildcard->pattern);
-    Curl_safefree(ftp_tmp);
+    free(ftp_tmp);
     return CURLE_OUT_OF_MEMORY;
   }
 
@@ -3868,13 +3886,13 @@ static CURLcode init_wc_data(struct connectdata *conn)
     conn->data->set.ftp_filemethod = FTPFILE_MULTICWD;
 
   /* try to parse ftp url */
-  ret = ftp_parse_url_path(conn);
-  if(ret) {
+  result = ftp_parse_url_path(conn);
+  if(result) {
     Curl_safefree(wildcard->pattern);
     wildcard->tmp_dtor(wildcard->tmp);
     wildcard->tmp_dtor = ZERO_NULL;
     wildcard->tmp = NULL;
-    return ret;
+    return result;
   }
 
   wildcard->path = strdup(conn->data->state.path);
@@ -3903,16 +3921,16 @@ static CURLcode init_wc_data(struct connectdata *conn)
 static CURLcode wc_statemach(struct connectdata *conn)
 {
   struct WildcardData * const wildcard = &(conn->data->wildcard);
-  CURLcode ret = CURLE_OK;
+  CURLcode result = CURLE_OK;
 
   switch (wildcard->state) {
   case CURLWC_INIT:
-    ret = init_wc_data(conn);
+    result = init_wc_data(conn);
     if(wildcard->state == CURLWC_CLEAN)
       /* only listing! */
       break;
     else
-      wildcard->state = ret ? CURLWC_ERROR : CURLWC_MATCHING;
+      wildcard->state = result ? CURLWC_ERROR : CURLWC_MATCHING;
     break;
 
   case CURLWC_MATCHING: {
@@ -3976,10 +3994,9 @@ static CURLcode wc_statemach(struct connectdata *conn)
     if(finfo->flags & CURLFINFOFLAG_KNOWN_SIZE)
       ftpc->known_filesize = finfo->size;
 
-    ret = ftp_parse_url_path(conn);
-    if(ret) {
-      return ret;
-    }
+    result = ftp_parse_url_path(conn);
+    if(result)
+      return result;
 
     /* we don't need the Curl_fileinfo of first file anymore */
     Curl_llist_remove(wildcard->filelist, wildcard->filelist->head, NULL);
@@ -4003,19 +4020,19 @@ static CURLcode wc_statemach(struct connectdata *conn)
 
   case CURLWC_CLEAN: {
     struct ftp_wc_tmpdata *ftp_tmp = wildcard->tmp;
-    ret = CURLE_OK;
-    if(ftp_tmp) {
-      ret = Curl_ftp_parselist_geterror(ftp_tmp->parser);
-    }
-    wildcard->state = ret ? CURLWC_ERROR : CURLWC_DONE;
+    result = CURLE_OK;
+    if(ftp_tmp)
+      result = Curl_ftp_parselist_geterror(ftp_tmp->parser);
+
+    wildcard->state = result ? CURLWC_ERROR : CURLWC_DONE;
   } break;
 
   case CURLWC_DONE:
   case CURLWC_ERROR:
     break;
   }
 
-  return ret;
+  return result;
 }
 
 /***********************************************************************
@@ -4029,31 +4046,31 @@ static CURLcode wc_statemach(struct connectdata *conn)
  */
 static CURLcode ftp_do(struct connectdata *conn, bool *done)
 {
-  CURLcode retcode = CURLE_OK;
+  CURLcode result = CURLE_OK;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
 
   *done = FALSE; /* default to false */
   ftpc->wait_data_conn = FALSE; /* default to no such wait */
 
   if(conn->data->set.wildcardmatch) {
-    retcode = wc_statemach(conn);
+    result = wc_statemach(conn);
     if(conn->data->wildcard.state == CURLWC_SKIP ||
       conn->data->wildcard.state == CURLWC_DONE) {
       /* do not call ftp_regular_transfer */
       return CURLE_OK;
     }
-    if(retcode) /* error, loop or skipping the file */
-      return retcode;
+    if(result) /* error, loop or skipping the file */
+      return result;
   }
   else { /* no wildcard FSM needed */
-    retcode = ftp_parse_url_path(conn);
-    if(retcode)
-      return retcode;
+    result = ftp_parse_url_path(conn);
+    if(result)
+      return result;
   }
 
-  retcode = ftp_regular_transfer(conn, done);
+  result = ftp_regular_transfer(conn, done);
 
-  return retcode;
+  return result;
 }
 
 
@@ -4065,7 +4082,7 @@ CURLcode Curl_ftpsendf(struct connectdata *conn,
   char s[SBUF_SIZE];
   size_t write_len;
   char *sptr=s;
-  CURLcode res = CURLE_OK;
+  CURLcode result = CURLE_OK;
 #ifdef HAVE_GSSAPI
   enum protection_level data_sec = conn->data_prot;
 #endif
@@ -4080,23 +4097,23 @@ CURLcode Curl_ftpsendf(struct connectdata *conn,
 
   bytes_written=0;
 
-  res = Curl_convert_to_network(conn->data, s, write_len);
+  result = Curl_convert_to_network(conn->data, s, write_len);
   /* Curl_convert_to_network calls failf if unsuccessful */
-  if(res)
-    return(res);
+  if(result)
+    return result;
 
   for(;;) {
 #ifdef HAVE_GSSAPI
     conn->data_prot = PROT_CMD;
 #endif
-    res = Curl_write(conn, conn->sock[FIRSTSOCKET], sptr, write_len,
-                     &bytes_written);
+    result = Curl_write(conn, conn->sock[FIRSTSOCKET], sptr, write_len,
+                        &bytes_written);
 #ifdef HAVE_GSSAPI
     DEBUGASSERT(data_sec > PROT_NONE && data_sec < PROT_LAST);
     conn->data_prot = data_sec;
 #endif
 
-    if(CURLE_OK != res)
+    if(result)
       break;
 
     if(conn->data->set.verbose)
@@ -4111,7 +4128,7 @@ CURLcode Curl_ftpsendf(struct connectdata *conn,
       break;
   }
 
-  return res;
+  return result;
 }
 
 /***********************************************************************
@@ -4182,14 +4199,10 @@ static CURLcode ftp_disconnect(struct connectdata *conn, bool dead_connection)
   }
 
   freedirs(ftpc);
-  if(ftpc->prevpath) {
-    free(ftpc->prevpath);
-    ftpc->prevpath = NULL;
-  }
-  if(ftpc->server_os) {
-    free(ftpc->server_os);
-    ftpc->server_os = NULL;
-  }
+  free(ftpc->prevpath);
+  ftpc->prevpath = NULL;
+  free(ftpc->server_os);
+  ftpc->server_os = NULL;
 
   Curl_pp_disconnect(pp);
 
@@ -4480,7 +4493,7 @@ CURLcode ftp_regular_transfer(struct connectdata *conn,
                        &connected, /* have we connected after PASV/PORT */
                        dophase_done); /* all commands in the DO-phase done? */
 
-  if(CURLE_OK == result) {
+  if(!result) {
 
     if(!*dophase_done)
       /* the DO phase has not completed yet */