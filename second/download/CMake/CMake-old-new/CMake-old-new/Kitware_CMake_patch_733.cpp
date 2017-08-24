@@ -1,25 +1,25 @@
-/*****************************************************************************
+/***************************************************************************
  *                                  _   _ ____  _     
  *  Project                     ___| | | |  _ \| |    
  *                             / __| | | | |_) | |    
  *                            | (__| |_| |  _ <| |___ 
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 2001, Daniel Stenberg, <daniel@haxx.se>, et al.
- *
- * In order to be useful for every potential user, curl and libcurl are
- * dual-licensed under the MPL and the MIT/X-derivate licenses.
+ * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
+ * This software is licensed as described in the file COPYING, which
+ * you should have received as part of this distribution. The terms
+ * are also available at http://curl.haxx.se/docs/copyright.html.
+ * 
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
- * furnished to do so, under the terms of the MPL or the MIT/X-derivate
- * licenses. You may pick one of these licenses.
+ * furnished to do so, under the terms of the COPYING file.
  *
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
  * $Id$
- *****************************************************************************/
+ ***************************************************************************/
 
 /* -- WIN32 approved -- */
 
@@ -72,6 +72,10 @@
 #include <inet.h>
 #endif
 
+#ifdef HAVE_SETJMP_H
+#include <setjmp.h>
+#endif
+
 #ifndef HAVE_SELECT
 #error "We can't compile without select() support!"
 #endif
@@ -107,6 +111,7 @@
 #include "ldap.h"
 #include "url.h"
 #include "connect.h"
+#include "ca-bundle.h"
 
 #include <curl/types.h>
 
@@ -120,6 +125,7 @@
 #ifdef KRB4
 #include "security.h"
 #endif
+
 /* The last #include file should be: */
 #ifdef MALLOCDEBUG
 #include "memdebug.h"
@@ -138,11 +144,17 @@ static unsigned int ConnectionStore(struct SessionHandle *data,
 #ifndef RETSIGTYPE
 #define RETSIGTYPE void
 #endif
+#ifdef HAVE_SIGSETJMP
+extern sigjmp_buf curl_jmpenv;
+#endif
 static
 RETSIGTYPE alarmfunc(int signal)
 {
   /* this is for "-ansi -Wall -pedantic" to stop complaining!   (rabe) */
   (void)signal;
+#ifdef HAVE_SIGSETJMP
+  siglongjmp(curl_jmpenv, 1);
+#endif
   return;
 }
 #endif
@@ -167,6 +179,13 @@ CURLcode Curl_close(struct SessionHandle *data)
   Curl_SSL_Close_All(data);
 #endif
 
+  /* No longer a dirty share, if it exists */
+  if (data->share)
+    data->share->dirty--;
+
+  if(data->change.cookielist) /* clean up list if any */
+    curl_slist_free_all(data->change.cookielist);
+
   if(data->state.auth_host)
     free(data->state.auth_host);
 
@@ -182,11 +201,13 @@ CURLcode Curl_close(struct SessionHandle *data)
   if(data->state.headerbuff)
     free(data->state.headerbuff);
 
+#ifndef CURL_DISABLE_HTTP
   if(data->set.cookiejar)
     /* we have a "destination" for all the cookies to get dumped to */
     Curl_cookie_output(data->cookies, data->set.cookiejar);
     
   Curl_cookie_cleanup(data->cookies);
+#endif
 
   /* free the connection cache */
   free(data->state.connects);
@@ -262,7 +283,11 @@ CURLcode Curl_open(struct SessionHandle **curl)
 
   /* Set the default size of the SSL session ID cache */
   data->set.ssl.numsessions = 5;
+
+  data->set.proxyport = 1080;
   
+  data->set.proxytype = CURLPROXY_HTTP; /* defaults to HTTP proxy */
+
   /* create an array with connection data struct pointers */
   data->state.numconnects = 5; /* hard-coded right now */
   data->state.connects = (struct connectdata **)
@@ -272,12 +297,23 @@ CURLcode Curl_open(struct SessionHandle **curl)
     free(data);
     return CURLE_OUT_OF_MEMORY;
   }
-  
+
+  /*
+   * libcurl 7.10 introduces SSL verification *by default*! This needs to be
+   * switched off unless wanted.
+   */
+  data->set.ssl.verifypeer = TRUE;
+  data->set.ssl.verifyhost = 2;
+#ifdef CURL_CA_BUNDLE
+  /* This is our prefered CA cert bundle since install time */
+  data->set.ssl.CAfile = (char *)CURL_CA_BUNDLE;
+#endif
+
+
   memset(data->state.connects, 0,
          sizeof(struct connectdata *)*data->state.numconnects);
 
   *curl = data;
-
   return CURLE_OK;
 }
 
@@ -439,7 +475,7 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
     /*
      * Parse the $HOME/.netrc file
      */
-    data->set.use_netrc = va_arg(param, long)?TRUE:FALSE;
+    data->set.use_netrc = va_arg(param, long);
     break;
   case CURLOPT_FOLLOWLOCATION:
     /*
@@ -493,13 +529,36 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
     data->set.ssl.version = va_arg(param, long);
     break;
 
+  case CURLOPT_COOKIESESSION:
+    /*
+     * Set this option to TRUE to start a new "cookie session". It will
+     * prevent the forthcoming read-cookies-from-file actions to accept
+     * cookies that are marked as being session cookies, as they belong to a
+     * previous session.
+     *
+     * In the original Netscape cookie spec, "session cookies" are cookies
+     * with no expire date set. RFC2109 describes the same action if no
+     * 'Max-Age' is set and RFC2965 includes the RFC2109 description and adds
+     * a 'Discard' action that can enforce the discard even for cookies that
+     * have a Max-Age.
+     *
+     * We run mostly with the original cookie spec, as hardly anyone implements
+     * anything else.
+     */
+    data->set.cookiesession = (bool)va_arg(param, long);
+    break;
+
+#ifndef CURL_DISABLE_HTTP
   case CURLOPT_COOKIEFILE:
     /*
      * Set cookie file to read and parse. Can be used multiple times.
      */
     cookiefile = (char *)va_arg(param, void *);
     if(cookiefile)
-      data->cookies = Curl_cookie_init(cookiefile, data->cookies);
+      /* append the cookie file name to the list of file names, and deal with
+         them later */
+      data->change.cookielist =
+        curl_slist_append(data->change.cookielist, cookiefile);
     break;
 
   case CURLOPT_COOKIEJAR:
@@ -512,8 +571,11 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
      * Activate the cookie parser. This may or may not already
      * have been made.
      */
-    data->cookies = Curl_cookie_init(NULL, data->cookies);
+    data->cookies = Curl_cookie_init(NULL, data->cookies,
+                                     data->set.cookiesession);
     break;
+#endif
+
   case CURLOPT_WRITEHEADER:
     /*
      * Custom pointer to pass the header write callback function
@@ -634,8 +696,9 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
     data->set.use_port = va_arg(param, long);
     break;
   case CURLOPT_POST:
-    /* Does this option serve a purpose anymore? */
-
+    /* Does this option serve a purpose anymore? Yes it does, when
+       CURLOPT_POSTFIELDS isn't used and the POST data is read off the
+       callback! */
     if(va_arg(param, long))
       data->set.httpreq = HTTPREQ_POST;
     break;
@@ -673,7 +736,13 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
     break;
   case CURLOPT_PROXY:
     /*
-     * Set proxy server:port to use as HTTP proxy
+     * Set proxy server:port to use as HTTP proxy.
+     *
+     * If the proxy is set to "" we explicitly say that we don't want to use a
+     * proxy (even though there might be environment variables saying so).
+     *
+     * Setting it to NULL, means no proxy but allows the environment variables
+     * to decide for us.
      */
     if(data->change.proxy_alloc) {
       /*
@@ -723,6 +792,13 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
      */
     data->set.useragent = va_arg(param, char *);
     break;
+  case CURLOPT_ENCODING:
+    /*
+     * String to use at the value of Accept-Encoding header. 08/28/02 jhrg
+     */
+    data->set.encoding = va_arg(param, char *);
+    break;
+
   case CURLOPT_USERPWD:
     /*
      * user:password to use in the operation
@@ -752,7 +828,11 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
      * Progress callback function
      */
     data->set.fprogress = va_arg(param, curl_progress_callback);
-    data->progress.callback = TRUE; /* no longer internal */
+    if(data->set.fprogress)
+      data->progress.callback = TRUE; /* no longer internal */
+    else
+      data->progress.callback = FALSE; /* NULL enforces internal */
+
     break;
   case CURLOPT_PROGRESSDATA:
     /*
@@ -765,6 +845,13 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
      * Password prompt callback
      */
     data->set.fpasswd = va_arg(param, curl_passwd_callback);
+    /*
+     * if the callback provided is null, reset the default callback
+     */
+    if(!data->set.fpasswd)
+    {
+      data->set.fpasswd = my_getpass;
+    }
     break;
   case CURLOPT_PASSWDDATA:
     /*
@@ -790,12 +877,30 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
      */
     data->set.set_resume_from = va_arg(param, long);
     break;
+  case CURLOPT_DEBUGFUNCTION:
+    /*
+     * stderr write callback.
+     */
+    data->set.fdebug = va_arg(param, curl_debug_callback);
+    /*
+     * if the callback provided is NULL, it'll use the default callback
+     */
+    break;
+  case CURLOPT_DEBUGDATA:
+    /*
+     * Set to a void * that should receive all error writes. This
+     * defaults to CURLOPT_STDERR for normal operations.
+     */
+    data->set.debugdata = va_arg(param, void *);
+    break;
   case CURLOPT_STDERR:
     /*
      * Set to a FILE * that should receive all error writes. This
      * defaults to stderr for normal operations.
      */
     data->set.err = va_arg(param, FILE *);
+    if(!data->set.err)
+      data->set.err = stderr;
     break;
   case CURLOPT_HEADERFUNCTION:
     /*
@@ -928,17 +1033,64 @@ CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
      * Set CA info for SSL connection. Specify file name of the CA certificate
      */
     data->set.ssl.CAfile = va_arg(param, char *);
-    data->set.ssl.CApath = NULL; /*This does not work on windows.*/
+    break;
+  case CURLOPT_CAPATH:
+    /*
+     * Set CA path info for SSL connection. Specify directory name of the CA
+     * certificates which have been prepared using openssl c_rehash utility.
+     */
+    /* This does not work on windows. */
+    data->set.ssl.CApath = va_arg(param, char *);
     break;
   case CURLOPT_TELNETOPTIONS:
     /*
      * Set a linked list of telnet options
      */
     data->set.telnet_options = va_arg(param, struct curl_slist *);
     break;
+
+  case CURLOPT_BUFFERSIZE:
+    /*
+     * The application kindly asks for a differently sized receive buffer.
+     * If it seems reasonable, we'll use it.
+     */
+    data->set.buffer_size = va_arg(param, long);
+
+    if(data->set.buffer_size> (BUFSIZE -1 ))
+      data->set.buffer_size = 0; /* huge internal default */
+
+    break;
+
+  case CURLOPT_NOSIGNAL:
+    /*
+     * The application asks not to set any signal() or alarm() handlers,
+     * even when using a timeout.
+     */
+    data->set.no_signal = va_arg(param, long) ? TRUE : FALSE;
+    break;
+
+  case CURLOPT_SHARE:
+    {
+      curl_share *set;
+      set = va_arg(param, curl_share *);
+      if(data->share)
+        data->share->dirty--;
+
+      data->share = set;
+      data->share->dirty++;
+    }
+    break;
+
+  case CURLOPT_PROXYTYPE:
+    /*
+     * Set proxy type. HTTP/SOCKS4/SOCKS5
+     */
+    data->set.proxytype = va_arg(param, long);
+    break;
+
   default:
     /* unknown tag and its companion, just ignore: */
-    return CURLE_READ_ERROR; /* correct this */
+    return CURLE_FAILED_INIT; /* correct this */
   }
   return CURLE_OK;
 }
@@ -993,6 +1145,8 @@ CURLcode Curl_disconnect(struct connectdata *conn)
     free(conn->allocptr.uagent);
   if(conn->allocptr.userpwd)
     free(conn->allocptr.userpwd);
+  if(conn->allocptr.accept_encoding)
+    free(conn->allocptr.accept_encoding);
   if(conn->allocptr.rangeline)
     free(conn->allocptr.rangeline);
   if(conn->allocptr.ref)
@@ -1026,7 +1180,7 @@ static bool SocketIsDead(int sock)
   FD_SET(sock,&check_set); 
 
   to.tv_sec = 0; 
-  to.tv_usec = 1; 
+  to.tv_usec = 0; 
 
   sval = select(sock + 1, &check_set, 0, 0, &to);
   if(sval == 0)
@@ -1050,6 +1204,7 @@ ConnectionExists(struct SessionHandle *data,
   struct connectdata *check;
 
   for(i=0; i< data->state.numconnects; i++) {
+    bool match = FALSE;
     /*
      * Note that if we use a HTTP proxy, we check connections to that
      * proxy and not to the actual remote server.
@@ -1070,7 +1225,6 @@ ConnectionExists(struct SessionHandle *data,
       if(strequal(needle->protostr, check->protostr) &&
          strequal(needle->name, check->name) &&
          (needle->remote_port == check->remote_port) ) {
-        bool dead;
         if(strequal(needle->protostr, "FTP")) {
           /* This is FTP, verify that we're using the same name and
              password as well */
@@ -1080,27 +1234,7 @@ ConnectionExists(struct SessionHandle *data,
             continue;
           }
         }
-        dead = SocketIsDead(check->firstsocket);
-        if(dead) {
-          /*
-           * Even though the connection seems to have passed away, we could
-           * still make an effort to get the name information, as we intend to
-           * connect to the same host again.
-           *
-           * This is now subject to discussion. What do you think?
-           */
-          infof(data, "Connection %d seems to be dead!\n", i);
-          Curl_disconnect(check); /* disconnect resources */
-          data->state.connects[i]=NULL; /* nothing here */
-
-          /* There's no need to continue search, because we only store
-             one connection for each unique set of identifiers */
-          return FALSE;
-        }
-
-        *usethis = check;
-        return TRUE; /* yes, we found one to use! */
-        
+        match = TRUE;
       }
     }
     else { /* The requested needle connection is using a proxy,
@@ -1109,9 +1243,26 @@ ConnectionExists(struct SessionHandle *data,
          strequal(needle->proxyhost, check->proxyhost) &&
          needle->port == check->port) {
         /* This is the same proxy connection, use it! */
-        *usethis = check;
-        return TRUE;
+        match = TRUE;
+      }
+    }
+
+    if(match) {
+      bool dead = SocketIsDead(check->firstsocket);
+      if(dead) {
+        /*
+         */
+        infof(data, "Connection %d seems to be dead!\n", i);
+        Curl_disconnect(check); /* disconnect resources */
+        data->state.connects[i]=NULL; /* nothing here */
+
+        /* There's no need to continue searching, because we only store
+           one connection for each unique set of identifiers */
+        return FALSE;
       }
+
+      *usethis = check;
+      return TRUE; /* yes, we found one to use! */
     }
   }
   return FALSE; /* no matching connecting exists */
@@ -1213,7 +1364,197 @@ ConnectionStore(struct SessionHandle *data,
   return i;
 }
 
-static CURLcode ConnectPlease(struct connectdata *conn)
+/*
+ * This function logs in to a SOCKS5 proxy and sends the specifies the final
+ * desitination server.
+ */
+static int handleSock5Proxy(
+    const char *proxy_name,
+    const char *proxy_password,
+    struct connectdata *conn,
+    int sock)
+{
+  unsigned char socksreq[600]; /* room for large user/pw (255 max each) */
+  int actualread;
+  int written;
+  CURLcode result;
+
+  Curl_nonblock(sock, FALSE);
+
+  socksreq[0] = 5; /* version */
+  socksreq[1] = (char)(proxy_name[0] ? 2 : 1); /* number of methods (below) */
+  socksreq[2] = 0; /* no authentication */
+  socksreq[3] = 2; /* username/password */
+
+  result = Curl_write(conn, sock, (char *)socksreq, (2 + (int)socksreq[1]),
+                      &written);
+  if ((result != CURLE_OK) || (written != (2 + (int)socksreq[1]))) {
+    failf(conn->data, "Unable to send initial SOCKS5 request.");
+    return 1;
+  }
+
+  result=Curl_read(conn, sock, (char *)socksreq, 2, &actualread);
+  if ((result != CURLE_OK) || (actualread != 2)) {
+    failf(conn->data, "Unable to receive initial SOCKS5 response.");
+    return 1;
+  }
+
+  if (socksreq[0] != 5) {
+    failf(conn->data, "Received invalid version in initial SOCKS5 response.");
+    return 1;
+  }
+  if (socksreq[1] == 0) {
+    /* Nothing to do, no authentication needed */
+    ;
+  }
+  else if (socksreq[1] == 2) {
+    /* Needs user name and password */
+    int userlen, pwlen, len;
+
+    userlen = strlen(proxy_name);
+    pwlen = strlen(proxy_password);
+
+    /*   username/password request looks like
+     * +----+------+----------+------+----------+
+     * |VER | ULEN |  UNAME   | PLEN |  PASSWD  |
+     * +----+------+----------+------+----------+
+     * | 1  |  1   | 1 to 255 |  1   | 1 to 255 |
+     * +----+------+----------+------+----------+
+     */
+    len = 0;
+    socksreq[len++] = 1;    /* username/pw subnegotiation version */
+    socksreq[len++] = (char) userlen;
+    memcpy(socksreq + len, proxy_name, (int) userlen);
+    len += userlen;
+    socksreq[len++] = (char) pwlen;
+    memcpy(socksreq + len, proxy_password, (int) pwlen);
+    len += pwlen;
+
+    result = Curl_write(conn, sock, (char *)socksreq, len, &written);
+    if ((result != CURLE_OK) || (len != written)) {
+      failf(conn->data, "Failed to send SOCKS5 sub-negotiation request.");
+      return 1;
+    }
+
+    result=Curl_read(conn, sock, (char *)socksreq, 2, &actualread);
+    if ((result != CURLE_OK) || (actualread != 2)) {
+      failf(conn->data, "Unable to receive SOCKS5 sub-negotiation response.");
+      return 1;
+    }
+
+    if ((socksreq[0] != 5) || /* version */
+        (socksreq[1] != 0)) { /* status */
+      failf(conn->data, "User was rejected by the SOCKS5 server (%d %d).",
+            socksreq[0], socksreq[1]);
+      return 1;
+    }
+
+    /* Everything is good so far, user was authenticated! */
+  }
+  else {
+    /* error */
+    if (socksreq[1] == 1) {
+      failf(conn->data,
+            "SOCKS5 GSSAPI per-message authentication is not supported.");
+      return 1;
+    }
+    else if (socksreq[1] == 255) {
+      if (proxy_name[0] == 0) {
+        failf(conn->data,
+              "No authentication method was acceptable. (It is quite likely"
+              " that the SOCKS5 server wanted a username/password, since none"
+              " was supplied to the server on this connection.)");
+      }
+      else {            
+        failf(conn->data, "No authentication method was acceptable.");
+      }
+      return 1;
+    }
+    else {
+      failf(conn->data,
+            "Undocumented SOCKS5 mode attempted to be used by server.");
+      return 1;
+    }
+  }
+
+  /* Authentication is complete, now specify destination to the proxy */
+  socksreq[0] = 5; /* version (SOCKS5) */
+  socksreq[1] = 1; /* connect */
+  socksreq[2] = 0; /* must be zero */
+  socksreq[3] = 1; /* IPv4 = 1 */
+    
+  {
+#ifndef ENABLE_IPV6
+    struct Curl_dns_entry *dns;
+    Curl_addrinfo *hp=NULL;
+    dns = Curl_resolv(conn->data, conn->hostname, conn->remote_port);
+    /*
+     * We cannot use 'hostent' as a struct that Curl_resolv() returns.  It
+     * returns a Curl_addrinfo pointer that may not always look the same.
+     */
+    if(dns)
+      hp=dns->addr;
+    if (hp && hp->h_addr_list[0]) {
+      socksreq[4] = ((char*)hp->h_addr_list[0])[0];
+      socksreq[5] = ((char*)hp->h_addr_list[0])[1];
+      socksreq[6] = ((char*)hp->h_addr_list[0])[2];
+      socksreq[7] = ((char*)hp->h_addr_list[0])[3];
+
+      Curl_resolv_unlock(dns); /* not used anymore from now on */
+    }
+    else {
+      failf(conn->data, "Failed to resolve \"%s\" for SOCKS5 connect.",
+            conn->hostname);
+      return 1;
+    }
+#else
+    failf(conn->data,
+          "%s:%d has an internal error an needs to be fixed to work",
+          __FILE__, __LINE__);
+    return 1;
+#endif
+  }
+
+  *((unsigned short*)&socksreq[8]) = htons(conn->remote_port);
+
+  {
+    const int packetsize = 10;
+
+    result = Curl_write(conn, sock, (char *)socksreq, packetsize, &written);
+    if ((result != CURLE_OK) || (written != packetsize)) {
+      failf(conn->data, "Failed to send SOCKS5 connect request.");
+      return 1;
+    }
+
+    result = Curl_read(conn, sock, (char *)socksreq, packetsize, &actualread);
+    if ((result != CURLE_OK) || (actualread != packetsize)) {
+      failf(conn->data, "Failed to receive SOCKS5 connect request ack.");
+      return 1;
+    }
+
+    if (socksreq[0] != 5) { /* version */
+      failf(conn->data,
+            "SOCKS5 reply has wrong version, version should be 5.");
+      return 1;
+    }
+    if (socksreq[1] != 0) { /* Anything besides 0 is an error */
+        failf(conn->data,
+              "Can't complete SOCKS5 connection to %d.%d.%d.%d:%d. (%d)",
+              (unsigned char)socksreq[4], (unsigned char)socksreq[5],
+              (unsigned char)socksreq[6], (unsigned char)socksreq[7],
+              (unsigned int)ntohs(*(unsigned short*)(&socksreq[8])),
+              socksreq[1]);
+        return 1;
+    }
+  }
+
+  Curl_nonblock(sock, TRUE);
+  return 0; /* Proxy was successful! */
+}
+
+static CURLcode ConnectPlease(struct connectdata *conn,
+                              struct Curl_dns_entry *hostaddr,
+                              bool *connected)
 {
   CURLcode result;
   Curl_ipconnect *addr;
@@ -1222,28 +1563,130 @@ static CURLcode ConnectPlease(struct connectdata *conn)
    * Connect to server/proxy
    *************************************************************/
   result= Curl_connecthost(conn,
-                           conn->hostaddr,
+                           hostaddr,
                            conn->port,
                            &conn->firstsocket,
-                           &addr);
+                           &addr,
+                           connected);
   if(CURLE_OK == result) {
     /* All is cool, then we store the current information from the hostaddr
        struct to the serv_addr, as it might be needed later. The address
        returned from the function above is crucial here. */
+    conn->connect_addr = hostaddr;
+
 #ifdef ENABLE_IPV6
     conn->serv_addr = addr;
 #else
     memset((char *) &conn->serv_addr, '\0', sizeof(conn->serv_addr));
     memcpy((char *)&(conn->serv_addr.sin_addr),
            (struct in_addr *)addr, sizeof(struct in_addr));
-    conn->serv_addr.sin_family = conn->hostaddr->h_addrtype;
-    conn->serv_addr.sin_port = htons(conn->port);
+    conn->serv_addr.sin_family = hostaddr->addr->h_addrtype;
+    conn->serv_addr.sin_port = htons((unsigned short)conn->port);
 #endif
+
+    if (conn->data->set.proxytype == CURLPROXY_SOCKS5) {
+      return handleSock5Proxy(conn->data->state.proxyuser,
+                              conn->data->state.proxypasswd,
+                              conn,
+                              conn->firstsocket) ?
+        CURLE_COULDNT_CONNECT : CURLE_OK;
+    }
+    else if (conn->data->set.proxytype == CURLPROXY_HTTP) {
+      /* do nothing here. handled later. */
+    }
+    else {
+      failf(conn->data, "unknown proxytype option given");
+      return CURLE_COULDNT_CONNECT; 
+    }
   }
 
   return result;
 }
 
+static void verboseconnect(struct connectdata *conn,
+                           struct Curl_dns_entry *dns)
+{
+#ifdef HAVE_INET_NTOA_R
+  char ntoa_buf[64];
+#endif
+  struct SessionHandle *data = conn->data;
+
+  /* Figure out the ip-number and display the first host name it shows: */
+#ifdef ENABLE_IPV6
+  (void)dns; /* not used in the IPv6 enabled version */
+  {
+    char hbuf[NI_MAXHOST];
+#ifdef NI_WITHSCOPEID
+    const int niflags = NI_NUMERICHOST | NI_WITHSCOPEID;
+#else
+    const int niflags = NI_NUMERICHOST;
+#endif
+    struct addrinfo *ai = conn->serv_addr;
+
+    if (getnameinfo(ai->ai_addr, ai->ai_addrlen, hbuf, sizeof(hbuf), NULL, 0,
+        niflags)) {
+      snprintf(hbuf, sizeof(hbuf), "?");
+    }
+    if (ai->ai_canonname) {
+      infof(data, "Connected to %s (%s) port %d\n", ai->ai_canonname, hbuf,
+            conn->port);
+    } else {
+      infof(data, "Connected to %s port %d\n", hbuf, conn->port);
+    }
+  }
+#else
+  {
+    Curl_addrinfo *hostaddr=dns->addr;
+    struct in_addr in;
+    (void) memcpy(&in.s_addr, &conn->serv_addr.sin_addr, sizeof (in.s_addr));
+    infof(data, "Connected to %s (%s) port %d\n",
+          hostaddr?hostaddr->h_name:"",
+#if defined(HAVE_INET_NTOA_R)
+          inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf)),
+#else
+          inet_ntoa(in),
+#endif
+          conn->port);
+  }
+#endif
+}
+
+/*
+ * We have discovered that the TCP connection has been successful, we can now
+ * proceed with some action.
+ *
+ * If we're using the multi interface, this host address pointer is most
+ * likely NULL at this point as we can't keep the resolved info around. This
+ * may call for some reworking, like a reference counter in the struct or
+ * something. The hostaddr is not used for very much though, we have the
+ * 'serv_addr' field in the connectdata struct for most of it.
+ */
+CURLcode Curl_protocol_connect(struct connectdata *conn,
+                               struct Curl_dns_entry *hostaddr)
+{
+  struct SessionHandle *data = conn->data;
+  CURLcode result=CURLE_OK;
+  
+  Curl_pgrsTime(data, TIMER_CONNECT); /* connect done */
+
+  if(data->set.verbose)
+    verboseconnect(conn, hostaddr);
+
+  if(conn->curl_connect) {
+    /* is there a protocol-specific connect() procedure? */
+
+    /* set start time here for timeout purposes in the
+     * connect procedure, it is later set again for the
+     * progress meter purpose */
+    conn->now = Curl_tvnow();
+
+    /* Call the protocol-specific connect function */
+    result = conn->curl_connect(conn);
+  }
+
+  return result; /* pass back status */
+}
+
 static CURLcode CreateConnection(struct SessionHandle *data,
                                  struct connectdata **in_connect)
 {
@@ -1253,18 +1696,16 @@ static CURLcode CreateConnection(struct SessionHandle *data,
   char resumerange[40]="";
   struct connectdata *conn;
   struct connectdata *conn_temp;
-  char endbracket;
   int urllen;
-#ifdef HAVE_INET_NTOA_R
-  char ntoa_buf[64];
-#endif
+  struct Curl_dns_entry *hostaddr;
 #ifdef HAVE_ALARM
-  unsigned int prev_alarm;
+  unsigned int prev_alarm=0;
 #endif
+  char endbracket;
 
 #ifdef HAVE_SIGACTION
   struct sigaction keep_sigact;   /* store the old struct here */
-  bool keep_copysig;              /* did copy it? */
+  bool keep_copysig=FALSE;        /* did copy it? */
 #else
 #ifdef HAVE_SIGNAL
   void *keep_sigact;              /* store the old handler here */
@@ -1301,16 +1742,18 @@ static CURLcode CreateConnection(struct SessionHandle *data,
   conn->firstsocket = -1;     /* no file descriptor */
   conn->secondarysocket = -1; /* no file descriptor */
   conn->connectindex = -1;    /* no index */
-  conn->bits.httpproxy = data->change.proxy?TRUE:FALSE; /* proxy-or-not */
+  conn->bits.httpproxy = (data->change.proxy && *data->change.proxy &&
+                          (data->set.proxytype == CURLPROXY_HTTP))?
+    TRUE:FALSE; /* http proxy or not */
   conn->bits.use_range = data->set.set_range?TRUE:FALSE; /* range status */
-  conn->range = data->set.set_range;               /* clone the range setting */
+  conn->range = data->set.set_range;              /* clone the range setting */
   conn->resume_from = data->set.set_resume_from;   /* inherite resume_from */
 
   /* Default protocol-independent behavior doesn't support persistant
      connections, so we set this to force-close. Protocols that support
      this need to set this to FALSE in their "curl_do" functions. */
   conn->bits.close = TRUE;
-  
+
   /* inherite initial knowledge from the data struct */
   conn->bits.user_passwd = data->set.userpwd?1:0;
   conn->bits.proxy_user_passwd = data->set.proxyuserpwd?1:0;
@@ -1321,6 +1764,20 @@ static CURLcode CreateConnection(struct SessionHandle *data,
   /* Store creation time to help future close decision making */
   conn->created = Curl_tvnow();
 
+  /* Set the start time temporary to this creation time to allow easier
+     timeout checks before the transfer has started for real. The start time
+     is later set "for real" using Curl_pgrsStartNow(). */
+  conn->data->progress.start = conn->created; 
+
+  conn->bits.upload_chunky =
+    ((conn->protocol&PROT_HTTP) &&
+     data->set.upload &&
+     (data->set.infilesize == -1) &&
+     (data->set.httpversion != CURL_HTTP_VERSION_1_0))?
+    /* HTTP, upload, unknown file size and not HTTP 1.0 */
+    TRUE:
+  /* else, no chunky upload */
+  FALSE;
 
   /***********************************************************
    * We need to allocate memory to store the path in. We get the size of the
@@ -1410,22 +1867,25 @@ static CURLcode CreateConnection(struct SessionHandle *data,
        * is based on the first letters of the server name.
        */
 
-      if(strnequal(conn->gname, "FTP", 3)) {
+      /* Note: if you add a new protocol, please update the list in
+       * lib/version.c too! */
+
+      if(checkprefix("FTP", conn->gname)) {
         strcpy(conn->protostr, "ftp");
       }
-      else if(strnequal(conn->gname, "GOPHER", 6))
+      else if(checkprefix("GOPHER", conn->gname))
         strcpy(conn->protostr, "gopher");
 #ifdef USE_SSLEAY
-      else if(strnequal(conn->gname, "HTTPS", 5))
+      else if(checkprefix("HTTPS", conn->gname))
         strcpy(conn->protostr, "https");
-      else if(strnequal(conn->gname, "FTPS", 4))
+      else if(checkprefix("FTPS", conn->gname))
         strcpy(conn->protostr, "ftps");
 #endif /* USE_SSLEAY */
-      else if(strnequal(conn->gname, "TELNET", 6))
+      else if(checkprefix("TELNET", conn->gname))
         strcpy(conn->protostr, "telnet");
-      else if (strnequal(conn->gname, "DICT", sizeof("DICT")-1))
+      else if (checkprefix("DICT", conn->gname))
         strcpy(conn->protostr, "DICT");
-      else if (strnequal(conn->gname, "LDAP", sizeof("LDAP")-1))
+      else if (checkprefix("LDAP", conn->gname))
         strcpy(conn->protostr, "LDAP");
       else {
         strcpy(conn->protostr, "http");
@@ -1437,32 +1897,12 @@ static CURLcode CreateConnection(struct SessionHandle *data,
 
   buf = data->state.buffer; /* this is our buffer */
 
-  /*************************************************************
-   * Take care of user and password authentication stuff
-   *************************************************************/
-
-  if(conn->bits.user_passwd && !data->set.use_netrc) {
-    data->state.user[0] =0;
-    data->state.passwd[0]=0;
-
-    if(*data->set.userpwd != ':') {
-      /* the name is given, get user+password */
-      sscanf(data->set.userpwd, "%127[^:]:%127[^\n]",
-             data->state.user, data->state.passwd);
-    }
-    else
-      /* no name given, get the password only */
-      sscanf(data->set.userpwd+1, "%127[^\n]", data->state.passwd);
-
-    /* check for password, if no ask for one */
-    if( !data->state.passwd[0] ) {
-      if(!data->set.fpasswd ||
-         data->set.fpasswd(data->set.passwd_client,
-                       "password:", data->state.passwd,
-                           sizeof(data->state.passwd)))
-        return CURLE_BAD_PASSWORD_ENTERED;
-    }
-  }
+  /*
+   * So if the URL was A://B/C,
+   *   conn->protostr is A
+   *   conn->gname is B
+   *   conn->path is /C
+   */
 
   /*************************************************************
    * Take care of proxy authentication stuff
@@ -1482,12 +1922,13 @@ static CURLcode CreateConnection(struct SessionHandle *data,
 
     /* check for password, if no ask for one */
     if( !data->state.proxypasswd[0] ) {
-      if(!data->set.fpasswd ||
-         data->set.fpasswd( data->set.passwd_client,
-                        "proxy password:",
-                        data->state.proxypasswd,
-                        sizeof(data->state.proxypasswd)))
+      if(data->set.fpasswd( data->set.passwd_client,
+                            "proxy password:",
+                            data->state.proxypasswd,
+                            sizeof(data->state.proxypasswd))) {
+        failf(data, "Bad password from password callback");
         return CURLE_BAD_PASSWORD_ENTERED;
+      }
     }
 
   }
@@ -1537,10 +1978,17 @@ static CURLcode CreateConnection(struct SessionHandle *data,
 
       nope=no_proxy?strtok_r(no_proxy, ", ", &no_proxy_tok_buf):NULL;
       while(nope) {
-        if(strlen(nope) <= strlen(conn->name)) {
+        unsigned int namelen;
+        char *endptr = strchr(conn->name, ':');
+        if(endptr)
+          namelen=endptr-conn->name;
+        else
+          namelen=strlen(conn->name);
+
+        if(strlen(nope) <= namelen) {
           char *checkn=
-            conn->name + strlen(conn->name) - strlen(nope);
-          if(strnequal(nope, checkn, strlen(nope))) {
+            conn->name + namelen - strlen(nope);
+          if(checkprefix(nope, checkn)) {
             /* no proxy for this host! */
             break;
           }
@@ -1622,6 +2070,7 @@ static CURLcode CreateConnection(struct SessionHandle *data,
     conn->protocol &= ~PROT_MISSING; /* switch that one off again */
   }
 
+#ifndef CURL_DISABLE_HTTP
   /************************************************************
    * RESUME on a HTTP page is a tricky business. First, let's just check that
    * 'range' isn't used, then set the range parameter and leave the resume as
@@ -1640,29 +2089,37 @@ static CURLcode CreateConnection(struct SessionHandle *data,
       conn->bits.use_range = 1; /* switch on range usage */
     }
   }
-
+#endif
   /*************************************************************
    * Setup internals depending on protocol
    *************************************************************/
 
   if (strequal(conn->protostr, "HTTP")) {
+#ifndef CURL_DISABLE_HTTP
     conn->port = (data->set.use_port && data->state.allow_port)?
       data->set.use_port:PORT_HTTP;
     conn->remote_port = PORT_HTTP;
     conn->protocol |= PROT_HTTP;
     conn->curl_do = Curl_http;
+    conn->curl_do_more = NULL;
     conn->curl_done = Curl_http_done;
     conn->curl_connect = Curl_http_connect;
+#else
+    failf(data, LIBCURL_NAME
+          " was built with HTTP disabled, http: not supported!");
+    return CURLE_UNSUPPORTED_PROTOCOL;
+#endif
   }
   else if (strequal(conn->protostr, "HTTPS")) {
-#ifdef USE_SSLEAY
+#if defined(USE_SSLEAY) && !defined(CURL_DISABLE_HTTP)
 
     conn->port = (data->set.use_port && data->state.allow_port)?
       data->set.use_port:PORT_HTTPS;
     conn->remote_port = PORT_HTTPS;
     conn->protocol |= PROT_HTTP|PROT_HTTPS|PROT_SSL;
 
     conn->curl_do = Curl_http;
+    conn->curl_do_more = NULL;
     conn->curl_done = Curl_http_done;
     conn->curl_connect = Curl_http_connect;
 
@@ -1673,6 +2130,7 @@ static CURLcode CreateConnection(struct SessionHandle *data,
 #endif /* !USE_SSLEAY */
   }
   else if (strequal(conn->protostr, "GOPHER")) {
+#ifndef CURL_DISABLE_GOPHER
     conn->port = (data->set.use_port && data->state.allow_port)?
       data->set.use_port:PORT_GOPHER;
     conn->remote_port = PORT_GOPHER;
@@ -1684,10 +2142,18 @@ static CURLcode CreateConnection(struct SessionHandle *data,
       }
     conn->protocol |= PROT_GOPHER;
     conn->curl_do = Curl_http;
+    conn->curl_do_more = NULL;
     conn->curl_done = Curl_http_done;
+#else
+    failf(data, LIBCURL_NAME
+          " was built with GOPHER disabled, gopher: not supported!");
+#endif
   }
   else if(strequal(conn->protostr, "FTP") ||
           strequal(conn->protostr, "FTPS")) {
+
+/* MN 06/07/02 */
+#ifndef CURL_DISABLE_FTP
     char *type;
 
     if(strequal(conn->protostr, "FTPS")) {
@@ -1706,6 +2172,7 @@ static CURLcode CreateConnection(struct SessionHandle *data,
     conn->protocol |= PROT_FTP;
 
     if(data->change.proxy &&
+       *data->change.proxy &&
        !data->set.tunnel_thru_httpproxy) {
       /* Unless we have asked to tunnel ftp operations through the proxy, we
          switch and use HTTP operations only */
@@ -1715,11 +2182,17 @@ static CURLcode CreateConnection(struct SessionHandle *data,
         failf(data, "ftps does not work through http proxy!");
         return CURLE_UNSUPPORTED_PROTOCOL;
       }
+#ifndef CURL_DISABLE_HTTP
       conn->curl_do = Curl_http;
       conn->curl_done = Curl_http_done;
+#else
+      failf(data, "FTP over http proxy requires HTTP support built-in!");
+      return CURLE_UNSUPPORTED_PROTOCOL;
+#endif
     }
     else {
       conn->curl_do = Curl_ftp;
+      conn->curl_do_more = Curl_ftp_nextconnect;
       conn->curl_done = Curl_ftp_done;
       conn->curl_connect = Curl_ftp_connect;
       conn->curl_disconnect = Curl_ftp_disconnect;
@@ -1735,7 +2208,7 @@ static CURLcode CreateConnection(struct SessionHandle *data,
     }
     if(type) {
       char command;
-      *type=0;
+      *type=0;                     /* it was in the middle of the hostname */
       command = toupper(type[6]);
       switch(command) {
       case 'A': /* ASCII mode */
@@ -1751,8 +2224,16 @@ static CURLcode CreateConnection(struct SessionHandle *data,
         break;
       }
     }
+
+/* MN 06/07/02 */
+#else /* CURL_DISABLE_FTP */
+    failf(data, LIBCURL_NAME
+          " was built with FTP disabled, ftp/ftps: not supported!");
+    return CURLE_UNSUPPORTED_PROTOCOL;
+#endif
   }
   else if(strequal(conn->protostr, "TELNET")) {
+#ifndef CURL_DISABLE_TELNET
     /* telnet testing factory */
     conn->protocol |= PROT_TELNET;
 
@@ -1761,24 +2242,39 @@ static CURLcode CreateConnection(struct SessionHandle *data,
     conn->remote_port = PORT_TELNET;
     conn->curl_do = Curl_telnet;
     conn->curl_done = Curl_telnet_done;
+#else
+    failf(data, LIBCURL_NAME
+          " was built with TELNET disabled!");
+#endif
   }
   else if (strequal(conn->protostr, "DICT")) {
+#ifndef CURL_DISABLE_DICT
     conn->protocol |= PROT_DICT;
     conn->port = (data->set.use_port && data->state.allow_port)?
       data->set.use_port:PORT_DICT;
     conn->remote_port = PORT_DICT;
     conn->curl_do = Curl_dict;
     conn->curl_done = NULL; /* no DICT-specific done */
+#else
+    failf(data, LIBCURL_NAME
+          " was built with DICT disabled!");
+#endif
   }
   else if (strequal(conn->protostr, "LDAP")) {
+#ifndef CURL_DISABLE_LDAP
     conn->protocol |= PROT_LDAP;
     conn->port = (data->set.use_port && data->state.allow_port)?
       data->set.use_port:PORT_LDAP;
     conn->remote_port = PORT_LDAP;
     conn->curl_do = Curl_ldap;
     conn->curl_done = NULL; /* no LDAP-specific done */
+#else
+    failf(data, LIBCURL_NAME
+          " was built with LDAP disabled!");
+#endif
   }
   else if (strequal(conn->protostr, "FILE")) {
+#ifndef CURL_DISABLE_FILE
     conn->protocol |= PROT_FILE;
 
     conn->curl_do = Curl_file;
@@ -1795,6 +2291,10 @@ static CURLcode CreateConnection(struct SessionHandle *data,
     }
 
     return result;
+#else
+    failf(data, LIBCURL_NAME
+          " was built with FILE disabled!");
+#endif
   }
   else {
     /* We fell through all checks and thus we don't support the specified
@@ -1804,117 +2304,55 @@ static CURLcode CreateConnection(struct SessionHandle *data,
   }
 
   /*************************************************************
-   * .netrc scanning coming up
-   *************************************************************/
-  if(data->set.use_netrc) {
-    if(Curl_parsenetrc(conn->hostname,
-                       data->state.user,
-                       data->state.passwd)) {
-      infof(data, "Couldn't find host %s in the .netrc file, using defaults",
-            conn->hostname);
-    }
-    else
-      conn->bits.user_passwd = 1; /* enable user+password */
-
-    /* weather we failed or not, we don't know which fields that were filled
-       in anyway */
-    if(!data->state.user[0])
-      strcpy(data->state.user, CURL_DEFAULT_USER);
-    if(!data->state.passwd[0])
-      strcpy(data->state.passwd, CURL_DEFAULT_PASSWORD);
-  }
-  else if(!(conn->bits.user_passwd) &&
-          (conn->protocol & (PROT_FTP|PROT_HTTP)) ) {
-    /* This is a FTP or HTTP URL, and we haven't got the user+password in
-     * the extra parameter, we will now try to extract the possible
-     * user+password pair in a string like:
-     * ftp://user:password@ftp.my.site:8021/README */
-    char *ptr=NULL; /* assign to remove possible warnings */
-    if((ptr=strchr(conn->name, '@'))) {
-      /* there's a user+password given here, to the left of the @ */
-
-      data->state.user[0] =0;
-      data->state.passwd[0]=0;
-
-      if(*conn->name != ':') {
-        /* the name is given, get user+password */
-        sscanf(conn->name, "%127[^:@]:%127[^@]",
-               data->state.user, data->state.passwd);
-      }
-      else
-        /* no name given, get the password only */
-        sscanf(conn->name+1, "%127[^@]", data->state.passwd);
-
-      if(data->state.user[0]) {
-        char *newname=curl_unescape(data->state.user, 0);
-        if(strlen(newname) < sizeof(data->state.user)) {
-          strcpy(data->state.user, newname);
-        }
-        /* if the new name is longer than accepted, then just use
-           the unconverted name, it'll be wrong but what the heck */
-        free(newname);
-      }
-
-      /* check for password, if no ask for one */
-      if( !data->state.passwd[0] ) {
-        if(!data->set.fpasswd ||
-           data->set.fpasswd(data->set.passwd_client,
-                             "password:", data->state.passwd,
-                             sizeof(data->state.passwd)))
-          return CURLE_BAD_PASSWORD_ENTERED;
-      }
-      else {
-        /* we have a password found in the URL, decode it! */
-        char *newpasswd=curl_unescape(data->state.passwd, 0);
-        if(strlen(newpasswd) < sizeof(data->state.passwd)) {
-          strcpy(data->state.passwd, newpasswd);
-        }
-        free(newpasswd);
-      }
-
-      conn->name = ++ptr;
-      conn->bits.user_passwd=TRUE; /* enable user+password */
-    }
-    else {
-      strcpy(data->state.user, CURL_DEFAULT_USER);
-      strcpy(data->state.passwd, CURL_DEFAULT_PASSWORD);
-    }
-  }
-
-  /*************************************************************
    * Figure out the remote port number
    *
    * No matter if we use a proxy or not, we have to figure out the remote
    * port number of various reasons.
    *
    * To be able to detect port number flawlessly, we must not confuse them
    * IPv6-specified addresses in the [0::1] style. (RFC2732)
+   *
+   * The conn->name is currently [user:passwd@]host[:port] where host could
+   * be a hostname, IPv4 address or IPv6 address.
    *************************************************************/
-
   if((1 == sscanf(conn->name, "[%*39[0-9a-fA-F:.]%c", &endbracket)) &&
      (']' == endbracket)) {
-    /* This is a (IPv6-style) specified IP-address. We support _any_
-       IP within brackets to be really generic. */
-    conn->name++; /* pass the starting bracket */
+    /* this is a RFC2732-style specified IP-address */
+    conn->bits.ipv6_ip = TRUE;
 
+    conn->name++; /* pass the starting bracket */ 
+    conn->hostname++;
     tmp = strchr(conn->name, ']');
     *tmp = 0; /* zero terminate */
-
     tmp++; /* pass the ending bracket */
     if(':' != *tmp)
       tmp = NULL; /* no port number available */
   }
-  else {
-    /* traditional IPv4-style port-extracting */
-    tmp = strchr(conn->name, ':');
-  }
+  else
+    tmp = strrchr(conn->name, ':');
 
   if (tmp) {
-    *tmp++ = '\0'; /* cut off the name there */
-    conn->remote_port = atoi(tmp);
+    char *rest;
+    unsigned long port;
+
+    port=strtoul(tmp+1, &rest, 10);  /* Port number must be decimal */
+
+    if (rest != (tmp+1) && *rest == '\0') {
+      /* The colon really did have only digits after it,
+       * so it is either a port number or a mistake */
+
+      if (port > 0xffff) {   /* Single unix standard says port numbers are
+                              * 16 bits long */
+        failf(data, "Port number too large: %lu", port);
+        return CURLE_URL_MALFORMAT;
+      }
+
+      *tmp = '\0'; /* cut off the name there */
+      conn->remote_port = (unsigned short)port;
+    }
   }
 
-  if(data->change.proxy) {
+  if(data->change.proxy && *data->change.proxy) {
     /* If this is supposed to use a proxy, we need to figure out the proxy
        host name name, so that we can re-use an existing connection
        that may exist registered to the same proxy host. */
@@ -1966,6 +2404,137 @@ static CURLcode CreateConnection(struct SessionHandle *data,
   }
 
   /*************************************************************
+   * Take care of user and password authentication stuff
+   *************************************************************/
+
+  /*
+   * Inputs: data->set.userpwd   (CURLOPT_USERPWD)
+   *         data->set.fpasswd   (CURLOPT_PASSWDFUNCTION)
+   *         data->set.use_netrc (CURLOPT_NETRC)
+   *         conn->hostname
+   *         netrc file
+   *         hard-coded defaults
+   *
+   * Outputs: (almost :- all currently undefined)
+   *          conn->bits.user_passwd  - non-zero if non-default passwords exist
+   *          conn->state.user        - non-zero length if defined
+   *          conn->state.passwd      -   ditto
+   *          conn->hostname          - remove user name and password
+   */
+
+  /* At this point, we're hoping all the other special cases have
+   * been taken care of, so conn->hostname is at most
+   *    [user[:password]]@]hostname
+   *
+   * We need somewhere to put the embedded details, so do that first.
+   */
+
+  data->state.user[0] =0;   /* to make everything well-defined */
+  data->state.passwd[0]=0;
+  
+  if (conn->protocol & (PROT_FTP|PROT_HTTP)) {
+    /* This is a FTP or HTTP URL, we will now try to extract the possible
+     * user+password pair in a string like:
+     * ftp://user:password@ftp.my.site:8021/README */
+    char *ptr=strchr(conn->name, '@');
+    char *userpass = conn->name;
+    if(ptr != NULL) {
+      /* there's a user+password given here, to the left of the @ */
+
+      conn->name = conn->hostname = ++ptr;
+
+      /* So the hostname is sane.  Only bother interpreting the
+       * results if we could care.  It could still be wasted
+       * work because it might be overtaken by the programmatically
+       * set user/passwd, but doing that first adds more cases here :-(
+       */
+
+      if (data->set.use_netrc != CURL_NETRC_REQUIRED) {
+        /* We could use the one in the URL */
+
+        conn->bits.user_passwd = 1; /* enable user+password */
+
+        if(*userpass != ':') {
+          /* the name is given, get user+password */
+          sscanf(userpass, "%127[^:@]:%127[^@]",
+                 data->state.user, data->state.passwd);
+        }
+        else
+          /* no name given, get the password only */
+          sscanf(userpass, ":%127[^@]", data->state.passwd);
+
+        if(data->state.user[0]) {
+          char *newname=curl_unescape(data->state.user, 0);
+          if(strlen(newname) < sizeof(data->state.user)) {
+            strcpy(data->state.user, newname);
+          }
+          /* if the new name is longer than accepted, then just use
+             the unconverted name, it'll be wrong but what the heck */
+          free(newname);
+        }
+        if (data->state.passwd[0]) {
+          /* we have a password found in the URL, decode it! */
+          char *newpasswd=curl_unescape(data->state.passwd, 0);
+          if(strlen(newpasswd) < sizeof(data->state.passwd)) {
+            strcpy(data->state.passwd, newpasswd);
+          }
+          free(newpasswd);
+        }
+      }
+    }
+  }
+
+  /* Programmatically set password:
+   *   - always applies, if available
+   *   - takes precedence over the values we just set above
+   * so scribble it over the top.
+   * User-supplied passwords are assumed not to need unescaping.
+   *
+   * user_password is set in "inherite initial knowledge' above,
+   * so it doesn't have to be set in this block
+   */
+  if (data->set.userpwd != NULL) {
+    if(*data->set.userpwd != ':') {
+      /* the name is given, get user+password */
+      sscanf(data->set.userpwd, "%127[^:]:%127[^\n]",
+             data->state.user, data->state.passwd);
+    }
+    else
+      /* no name given, get the password only */
+      sscanf(data->set.userpwd+1, "%127[^\n]", data->state.passwd);
+  }
+
+  if (data->set.use_netrc != CURL_NETRC_IGNORED &&
+      data->state.passwd[0] == '\0' ) {  /* need passwd */
+    if(Curl_parsenetrc(conn->hostname,
+                       data->state.user,
+                       data->state.passwd)) {
+      infof(data, "Couldn't find host %s in the .netrc file, using defaults",
+            conn->hostname);
+    } else
+      conn->bits.user_passwd = 1; /* enable user+password */
+  }
+
+  /* if we have a user but no password, ask for one */
+  if(conn->bits.user_passwd &&
+     !data->state.passwd[0] ) {
+    if(data->set.fpasswd(data->set.passwd_client,
+                         "password:", data->state.passwd,
+                         sizeof(data->state.passwd)))
+      return CURLE_BAD_PASSWORD_ENTERED;
+  }
+
+  /* So we could have a password but no user; that's just too bad. */
+
+  /* If our protocol needs a password and we have none, use the defaults */
+  if ( (conn->protocol & (PROT_FTP|PROT_HTTP)) &&
+       !conn->bits.user_passwd) {
+    strcpy(data->state.user, CURL_DEFAULT_USER);
+    strcpy(data->state.passwd, CURL_DEFAULT_PASSWORD);
+    /* This is the default password, so DON'T set conn->bits.user_passwd */
+  }
+
+  /*************************************************************
    * Check the current list of connections to see if we can
    * re-use an already existing one or if we have to create a
    * new one.
@@ -1988,6 +2557,10 @@ static CURLcode CreateConnection(struct SessionHandle *data,
       free(old_conn->proxyhost);
     conn = conn_temp;        /* use this connection from now on */
 
+    /* If we speak over a proxy, we need to copy the host name too, as it
+       might be another remote host even when re-using a connection */
+    strcpy(conn->gname, old_conn->gname); /* safe strcpy() */
+
     /* we need these pointers if we speak over a proxy */
     conn->hostname = conn->gname;
     conn->name = &conn->gname[old_conn->name - old_conn->gname];
@@ -2044,7 +2617,7 @@ static CURLcode CreateConnection(struct SessionHandle *data,
   /*************************************************************
    * Set timeout if that is being used
    *************************************************************/
-  if(data->set.timeout || data->set.connecttimeout) {
+  if((data->set.timeout || data->set.connecttimeout) && !data->set.no_signal) {
     /*************************************************************
      * Set signal handler to catch SIGALRM
      * Store the old value to be able to set it back later!
@@ -2089,41 +2662,39 @@ static CURLcode CreateConnection(struct SessionHandle *data,
   /*************************************************************
    * Resolve the name of the server or proxy
    *************************************************************/
-  if(!data->change.proxy) {
+  if(conn->bits.reuse) {
+    /* re-used connection, no resolving is necessary */
+    hostaddr = NULL;
+  }
+  else if(!data->change.proxy || !*data->change.proxy) {
     /* If not connecting via a proxy, extract the port from the URL, if it is
      * there, thus overriding any defaults that might have been set above. */
     conn->port =  conn->remote_port; /* it is the same port */
 
     /* Resolve target host right on */
-    if(!conn->hostaddr) {
-      /* it might already be set if reusing a connection */
-      conn->hostaddr = Curl_resolv(data, conn->name, conn->port,
-                                   &conn->hostent_buf);
-    }
-    if(!conn->hostaddr) {
+    hostaddr = Curl_resolv(data, conn->name, conn->port);
+
+    if(!hostaddr) {
       failf(data, "Couldn't resolve host '%s'", conn->name);
       result =  CURLE_COULDNT_RESOLVE_HOST;
       /* don't return yet, we need to clean up the timeout first */
     }
   }
-  else if(!conn->hostaddr) {
-    /* This is a proxy that hasn't been resolved yet. It may be resolved
-       if we're reusing an existing connection. */
+  else {
+    /* This is a proxy that hasn't been resolved yet. */
 
     /* resolve proxy */
-    /* it might already be set if reusing a connection */
-    conn->hostaddr = Curl_resolv(data, conn->proxyhost, conn->port,
-                                 &conn->hostent_buf);
+    hostaddr = Curl_resolv(data, conn->proxyhost, conn->port);
 
-    if(!conn->hostaddr) {
+    if(!hostaddr) {
       failf(data, "Couldn't resolve proxy '%s'", conn->proxyhost);
       result = CURLE_COULDNT_RESOLVE_PROXY;
       /* don't return yet, we need to clean up the timeout first */
     }
   }
   Curl_pgrsTime(data, TIMER_NAMELOOKUP);
 #ifdef HAVE_ALARM
-  if(data->set.timeout || data->set.connecttimeout) {
+  if((data->set.timeout || data->set.connecttimeout) && !data->set.no_signal) {
 #ifdef HAVE_SIGACTION
     if(keep_copysig) {
       /* we got a struct as it looked before, now put that one back nice
@@ -2185,7 +2756,8 @@ static CURLcode CreateConnection(struct SessionHandle *data,
    * Send user-agent to HTTP proxies even if the target protocol
    * isn't HTTP.
    *************************************************************/
-  if((conn->protocol&PROT_HTTP) || data->change.proxy) {
+  if((conn->protocol&PROT_HTTP) ||
+     (data->change.proxy && *data->change.proxy)) {
     if(data->set.useragent) {
       if(conn->allocptr.uagent)
         free(conn->allocptr.uagent);
@@ -2194,68 +2766,36 @@ static CURLcode CreateConnection(struct SessionHandle *data,
     }
   }
 
-  if(-1 == conn->firstsocket) {
-    /* Connect only if not already connected! */
-    result = ConnectPlease(conn);
-    if(CURLE_OK != result)
-      return result;
-
-    if(conn->curl_connect) {
-      /* is there a connect() procedure? */
-
-      /* set start time here for timeout purposes in the
-       * connect procedure, it is later set again for the
-       * progress meter purpose */
-      conn->now = Curl_tvnow();
-
-      /* Call the protocol-specific connect function */
-      result = conn->curl_connect(conn);
-      if(result != CURLE_OK)
-        return result; /* pass back errors */
-    }
+  if(data->set.encoding) {
+    if(conn->allocptr.accept_encoding)
+      free(conn->allocptr.accept_encoding);
+    conn->allocptr.accept_encoding =
+      aprintf("Accept-Encoding: %s\015\012", data->set.encoding);
   }
 
-  Curl_pgrsTime(data, TIMER_CONNECT); /* we're connected */
-
-  conn->now = Curl_tvnow(); /* time this *after* the connect is done */
   conn->bytecount = 0;
   conn->headerbytecount = 0;
   
-  /* Figure out the ip-number and display the first host name it shows: */
-#ifdef ENABLE_IPV6
-  {
-    char hbuf[NI_MAXHOST];
-#ifdef NI_WITHSCOPEID
-    const int niflags = NI_NUMERICHOST | NI_WITHSCOPEID;
-#else
-    const int niflags = NI_NUMERICHOST;
-#endif
-    struct addrinfo *ai = conn->serv_addr;
+  if(-1 == conn->firstsocket) {
+    bool connected;
 
-    if (getnameinfo(ai->ai_addr, ai->ai_addrlen, hbuf, sizeof(hbuf), NULL, 0,
-        niflags)) {
-      snprintf(hbuf, sizeof(hbuf), "?");
-    }
-    if (ai->ai_canonname) {
-      infof(data, "Connected to %s (%s) port %d\n", ai->ai_canonname, hbuf,
-            conn->port);
-    } else {
-      infof(data, "Connected to %s port %d\n", hbuf, conn->port);
-    }
+    /* Connect only if not already connected! */
+    result = ConnectPlease(conn, hostaddr, &connected);
+
+    if(connected)
+      result = Curl_protocol_connect(conn, hostaddr);
+
+    if(CURLE_OK != result)
+      return result;
   }
-#else
-  {
-    struct in_addr in;
-    (void) memcpy(&in.s_addr, &conn->serv_addr.sin_addr, sizeof (in.s_addr));
-    infof(data, "Connected to %s (%s)\n", conn->hostaddr->h_name,
-#if defined(HAVE_INET_NTOA_R)
-          inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf))
-#else
-          inet_ntoa(in)
-#endif
-          );
+  else {
+    Curl_pgrsTime(data, TIMER_CONNECT); /* we're connected already */
+    if(data->set.verbose)
+      verboseconnect(conn, hostaddr);
   }
-#endif
+
+  conn->now = Curl_tvnow(); /* time this *after* the connect is done, we
+                               set this here perhaps a second time */
 
 #ifdef __EMX__
   /* 20000330 mgs
@@ -2293,7 +2833,6 @@ CURLcode Curl_connect(struct SessionHandle *data,
   return code;
 }
 
-
 CURLcode Curl_done(struct connectdata *conn)
 {
   struct SessionHandle *data=conn->data;
@@ -2311,7 +2850,16 @@ CURLcode Curl_done(struct connectdata *conn)
     free(conn->newurl);
     conn->newurl = NULL;
   }
- 
+
+  if(conn->connect_addr)
+    Curl_resolv_unlock(conn->connect_addr); /* done with this */
+
+#if defined(MALLOCDEBUG) && defined(AGGRESIVE_TEST)
+  /* scan for DNS cache entries still marked as in use */
+  Curl_hash_apply(data->hostcache,
+                  NULL, Curl_scan_cache_used);
+#endif
+
   /* this calls the protocol-specific function pointer previously set */
   if(conn->curl_done)
     result = conn->curl_done(conn);
@@ -2341,13 +2889,15 @@ CURLcode Curl_do(struct connectdata **connp)
   struct connectdata *conn = *connp;
   struct SessionHandle *data=conn->data;
 
+  conn->bits.do_more = FALSE; /* by default there's no curl_do_more() to use */
+
   if(conn->curl_do) {
     /* generic protocol-specific function pointer set in curl_connect() */
     result = conn->curl_do(conn);
 
     /* This was formerly done in transfer.c, but we better do it here */
     
-    if((CURLE_WRITE_ERROR == result) && conn->bits.reuse) {
+    if((CURLE_SEND_ERROR == result) && conn->bits.reuse) {
       /* This was a re-use of a connection and we got a write error in the
        * DO-phase. Then we DISCONNECT this connection and have another attempt
        * to CONNECT and then DO again! The retry cannot possibly find another
@@ -2370,6 +2920,16 @@ CURLcode Curl_do(struct connectdata **connp)
   return result;
 }
 
+CURLcode Curl_do_more(struct connectdata *conn)
+{
+  CURLcode result=CURLE_OK;
+
+  if(conn->curl_do_more)
+    result = conn->curl_do_more(conn);
+
+  return result;
+}
+
 /*
  * local variables:
  * eval: (load-file "../curl-mode.el")