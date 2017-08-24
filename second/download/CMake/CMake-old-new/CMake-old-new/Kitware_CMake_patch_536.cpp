@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2006, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -25,7 +25,9 @@
 
 #ifndef WIN32
 /* headers for non-win32 */
+#ifdef HAVE_SYS_TIME_H
 #include <sys/time.h>
+#endif
 #ifdef HAVE_SYS_TYPES_H
 #include <sys/types.h>
 #endif
@@ -67,7 +69,7 @@
 #undef in_addr_t
 #define in_addr_t unsigned long
 #endif
-#ifdef  VMS
+#ifdef VMS
 #include <in.h>
 #include <inet.h>
 #endif
@@ -82,8 +84,7 @@
 #define FALSE 0
 #endif
 
-#ifdef WIN32
-#include <windows.h>
+#ifdef USE_WINSOCK
 #define EINPROGRESS WSAEINPROGRESS
 #define EWOULDBLOCK WSAEWOULDBLOCK
 #define EISCONN     WSAEISCONN
@@ -96,7 +97,12 @@
 #include "if2ip.h"
 #include "strerror.h"
 #include "connect.h"
-#include "curl_memory.h"
+#include "memory.h"
+#include "select.h"
+#include "url.h" /* for Curl_safefree() */
+#include "multiif.h"
+#include "sockaddr.h" /* required for Curl_sockaddr_storage */
+#include "inet_ntop.h"
 
 /* The last #include file should be: */
 #include "memdebug.h"
@@ -105,18 +111,18 @@ static bool verifyconnect(curl_socket_t sockfd, int *error);
 
 static curl_socket_t
 singleipconnect(struct connectdata *conn,
-                Curl_addrinfo *ai, /* start connecting to this */
+                const Curl_addrinfo *ai, /* start connecting to this */
                 long timeout_ms,
                 bool *connected);
 
 /*
- * Curl_ourerrno() returns the errno (or equivalent) on this platform to
- * hide platform specific for the function that calls this.
+ * Curl_sockerrno() returns the *socket-related* errno (or equivalent) on this
+ * platform to hide platform specific for the function that calls this.
  */
-int Curl_ourerrno(void)
+int Curl_sockerrno(void)
 {
-#ifdef WIN32
-  return (int)GetLastError();
+#ifdef USE_WINSOCK
+  return (int)WSAGetLastError();
 #else
   return errno;
 #endif
@@ -131,72 +137,62 @@ int Curl_nonblock(curl_socket_t sockfd,    /* operate on this */
                   int nonblock   /* TRUE or FALSE */)
 {
 #undef SETBLOCK
+#define SETBLOCK 0
 #ifdef HAVE_O_NONBLOCK
-    {
-    /* most recent unix versions */
-    int flags;
+  /* most recent unix versions */
+  int flags;
 
-    flags = fcntl(sockfd, F_GETFL, 0);
-    if (TRUE == nonblock)
-      return fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
-    else
-      return fcntl(sockfd, F_SETFL, flags & (~O_NONBLOCK));
-    }
+  flags = fcntl(sockfd, F_GETFL, 0);
+  if (TRUE == nonblock)
+    return fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
+  else
+    return fcntl(sockfd, F_SETFL, flags & (~O_NONBLOCK));
+#undef SETBLOCK
 #define SETBLOCK 1
 #endif
 
-#ifdef HAVE_FIONBIO
-    {
-    /* older unix versions */
-    int flags;
+#if defined(HAVE_FIONBIO) && (SETBLOCK == 0)
+  /* older unix versions */
+  int flags;
 
-    flags = nonblock;
-    return ioctl(sockfd, FIONBIO, &flags);
-    }
-#ifdef SETBLOCK
-# undef SETBLOCK
-#endif
+  flags = nonblock;
+  return ioctl(sockfd, FIONBIO, &flags);
+#undef SETBLOCK
 #define SETBLOCK 2
 #endif
 
-#ifdef HAVE_IOCTLSOCKET
+#if defined(HAVE_IOCTLSOCKET) && (SETBLOCK == 0)
   /* Windows? */
   unsigned long flags;
   flags = nonblock;
+
   return ioctlsocket(sockfd, FIONBIO, &flags);
+#undef SETBLOCK
 #define SETBLOCK 3
 #endif
 
-#ifdef HAVE_IOCTLSOCKET_CASE
+#if defined(HAVE_IOCTLSOCKET_CASE) && (SETBLOCK == 0)
   /* presumably for Amiga */
   return IoctlSocket(sockfd, FIONBIO, (long)nonblock);
-#ifdef SETBLOCK
-# undef SETBLOCK
-#endif
+#undef SETBLOCK
 #define SETBLOCK 4
 #endif
 
-#ifdef HAVE_SO_NONBLOCK
+#if defined(HAVE_SO_NONBLOCK) && (SETBLOCK == 0)
   /* BeOS */
   long b = nonblock ? 1 : 0;
   return setsockopt(sockfd, SOL_SOCKET, SO_NONBLOCK, &b, sizeof(b));
-#ifdef SETBLOCK
-# undef SETBLOCK
-#endif
+#undef SETBLOCK
 #define SETBLOCK 5
 #endif
 
 #ifdef HAVE_DISABLED_NONBLOCKING
-  (void)nonblock;
-  (void)sockfd;
   return 0; /* returns success */
-#ifdef SETBLOCK
-# undef SETBLOCK
-#endif
+#undef SETBLOCK
 #define SETBLOCK 6
 #endif
 
-#ifndef SETBLOCK
+#if (SETBLOCK == 0)
 #error "no non-blocking method was found/used/set"
 #endif
 }
@@ -219,30 +215,16 @@ static
 int waitconnect(curl_socket_t sockfd, /* socket */
                 long timeout_msec)
 {
-  fd_set fd;
-  fd_set errfd;
-  struct timeval interval;
   int rc;
 #ifdef mpeix
   /* Call this function once now, and ignore the results. We do this to
      "clear" the error state on the socket so that we can later read it
      reliably. This is reported necessary on the MPE/iX operating system. */
-  verifyconnect(sockfd, NULL);
+  (void)verifyconnect(sockfd, NULL);
 #endif
 
   /* now select() until we get connect or timeout */
-  FD_ZERO(&fd);
-  FD_SET(sockfd, &fd);
-
-  FD_ZERO(&errfd);
-  FD_SET(sockfd, &errfd);
-
-  interval.tv_sec = (int)(timeout_msec/1000);
-  timeout_msec -= interval.tv_sec*1000;
-
-  interval.tv_usec = timeout_msec*1000;
-
-  rc = select(sockfd+1, NULL, &fd, &errfd, &interval);
+  rc = Curl_select(CURL_SOCKET_BAD, sockfd, (int)timeout_msec);
   if(-1 == rc)
     /* error, no connect here, try next */
     return WAITCONN_SELECT_ERROR;
@@ -251,7 +233,7 @@ int waitconnect(curl_socket_t sockfd, /* socket */
     /* timeout, no connect today */
     return WAITCONN_TIMEOUT;
 
-  if(FD_ISSET(sockfd, &errfd))
+  if(rc & CSELECT_ERR)
     /* error condition caught */
     return WAITCONN_FDSET_ERROR;
 
@@ -262,14 +244,19 @@ int waitconnect(curl_socket_t sockfd, /* socket */
 static CURLcode bindlocal(struct connectdata *conn,
                           curl_socket_t sockfd)
 {
-#ifdef HAVE_INET_NTOA
-  bool bindworked = FALSE;
   struct SessionHandle *data = conn->data;
+  struct sockaddr_in me;
+  struct sockaddr *sock = NULL;  /* bind to this address */
+  socklen_t socksize; /* size of the data sock points to */
+  unsigned short port = data->set.localport; /* use this port number, 0 for
+                                                "random" */
+  /* how many port numbers to try to bind to, increasing one at a time */
+  int portnum = data->set.localportrange;
 
   /*************************************************************
    * Select device to bind socket to
    *************************************************************/
-  if (strlen(data->set.device)<255) {
+  if (data->set.device && (strlen(data->set.device)<255) ) {
     struct Curl_dns_entry *h=NULL;
     char myhost[256] = "";
     in_addr_t in;
@@ -288,8 +275,10 @@ static CURLcode bindlocal(struct connectdata *conn,
       if(rc == CURLRESOLV_PENDING)
         (void)Curl_wait_for_resolv(conn, &h);
 
-      if(h)
+      if(h) {
         was_iface = TRUE;
+        Curl_resolv_unlock(data, h);
+      }
     }
 
     if(!was_iface) {
@@ -301,9 +290,17 @@ static CURLcode bindlocal(struct connectdata *conn,
       if(rc == CURLRESOLV_PENDING)
         (void)Curl_wait_for_resolv(conn, &h);
 
-      if(h)
-        /* we know data->set.device is shorter than the myhost array */
-        strcpy(myhost, data->set.device);
+      if(h) {
+        if(in == CURL_INADDR_NONE)
+          /* convert the resolved address, sizeof myhost >= INET_ADDRSTRLEN */
+          Curl_inet_ntop(h->addr->ai_addr->sa_family,
+                         &((struct sockaddr_in*)h->addr->ai_addr)->sin_addr,
+                         myhost, sizeof myhost);
+        else
+          /* we know data->set.device is shorter than the myhost array */
+          strcpy(myhost, data->set.device);
+        Curl_resolv_unlock(data, h);
+      }
     }
 
     if(! *myhost) {
@@ -317,7 +314,7 @@ static CURLcode bindlocal(struct connectdata *conn,
       return CURLE_HTTP_PORT_FAILED;
     }
 
-    infof(data, "We bind local end to %s\n", myhost);
+    infof(data, "Bind local address to %s\n", myhost);
 
 #ifdef SO_BINDTODEVICE
     /* I am not sure any other OSs than Linux that provide this feature, and
@@ -335,7 +332,7 @@ static CURLcode bindlocal(struct connectdata *conn,
       if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
                      data->set.device, strlen(data->set.device)+1) != 0) {
         /* printf("Failed to BINDTODEVICE, socket: %d  device: %s error: %s\n",
-           sockfd, data->set.device, Curl_strerror(Curl_ourerrno())); */
+           sockfd, data->set.device, Curl_strerror(Curl_sockerrno())); */
         infof(data, "SO_BINDTODEVICE %s failed\n",
               data->set.device);
         /* This is typically "errno 1, error: Operation not permitted" if
@@ -345,75 +342,89 @@ static CURLcode bindlocal(struct connectdata *conn,
 #endif
 
     in=inet_addr(myhost);
-    if (CURL_INADDR_NONE != in) {
+    if (CURL_INADDR_NONE == in) {
+      failf(data,"couldn't find my own IP address (%s)", myhost);
+      return CURLE_HTTP_PORT_FAILED;
+    } /* end of inet_addr */
 
-      if ( h ) {
-        Curl_addrinfo *addr = h->addr;
+    if ( h ) {
+      Curl_addrinfo *addr = h->addr;
+      sock = addr->ai_addr;
+      socksize = addr->ai_addrlen;
+    }
+    else
+      return CURLE_HTTP_PORT_FAILED;
 
-        Curl_resolv_unlock(data, h);
-        /* we don't need it anymore after this function has returned */
+  }
+  else if(port) {
+    /* if a local port number is requested but no local IP, extract the
+       address from the socket */
+    memset(&me, 0, sizeof(struct sockaddr));
+    me.sin_family = AF_INET;
+    me.sin_addr.s_addr = INADDR_ANY;
 
-        if( bind(sockfd, addr->ai_addr, (socklen_t)addr->ai_addrlen) >= 0) {
-          /* we succeeded to bind */
-#ifdef ENABLE_IPV6
-          struct sockaddr_in6 add;
-#else
-          struct sockaddr_in add;
-#endif
+    sock = (struct sockaddr *)&me;
+    socksize = sizeof(struct sockaddr);
 
-#ifdef __hpux
-          int gsize = sizeof(add);
-#else
-          socklen_t gsize = sizeof(add);
-#endif
-          bindworked = TRUE;
+  }
+  else
+    /* no local kind of binding was requested */
+    return CURLE_OK;
 
-          if(getsockname(sockfd, (struct sockaddr *) &add,
-                         &gsize)<0) {
-            failf(data, "getsockname() failed");
-            return CURLE_HTTP_PORT_FAILED;
-          }
-        }
+  do {
 
-        if(!bindworked) {
-          failf(data, "%s", Curl_strerror(conn, Curl_ourerrno()));
-          return CURLE_HTTP_PORT_FAILED;
-        }
+    /* Set port number to bind to, 0 makes the system pick one */
+    if(sock->sa_family == AF_INET)
+      ((struct sockaddr_in *)sock)->sin_port = htons(port);
+#ifdef ENABLE_IPV6
+    else
+      ((struct sockaddr_in6 *)sock)->sin6_port = htons(port);
+#endif
+
+    if( bind(sockfd, sock, socksize) >= 0) {
+      /* we succeeded to bind */
+      struct Curl_sockaddr_storage add;
+      socklen_t size;
 
-      } /* end of if  h */
-      else {
-        failf(data,"could't find my own IP address (%s)", myhost);
+      size = sizeof(add);
+      if(getsockname(sockfd, (struct sockaddr *) &add, &size) < 0) {
+        failf(data, "getsockname() failed");
         return CURLE_HTTP_PORT_FAILED;
       }
-    } /* end of inet_addr */
-
-    else {
-      failf(data, "could't find my own IP address (%s)", myhost);
-      return CURLE_HTTP_PORT_FAILED;
+      /* We re-use/clobber the port variable here below */
+      if(((struct sockaddr *)&add)->sa_family == AF_INET)
+        port = ntohs(((struct sockaddr_in *)&add)->sin_port);
+#ifdef ENABLE_IPV6
+      else
+        port = ntohs(((struct sockaddr_in6 *)&add)->sin6_port);
+#endif
+      infof(data, "Local port: %d\n", port);
+      return CURLE_OK;
     }
+    if(--portnum > 0) {
+      infof(data, "Bind to local port %d failed, trying next\n", port);
+      port++; /* try next port */
+    }
+    else
+      break;
+  } while(1);
 
-    return CURLE_OK;
-
-  } /* end of device selection support */
-#endif /* end of HAVE_INET_NTOA */
-
+  data->state.os_errno = Curl_sockerrno();
+  failf(data, "bind failure: %s",
+        Curl_strerror(conn, data->state.os_errno));
   return CURLE_HTTP_PORT_FAILED;
+
 }
 
 /*
  * verifyconnect() returns TRUE if the connect really has happened.
  */
 static bool verifyconnect(curl_socket_t sockfd, int *error)
 {
-  bool rc;
+  bool rc = TRUE;
 #ifdef SO_ERROR
   int err = 0;
-#ifdef __hpux
-  int errSize = sizeof(err);
-#else
   socklen_t errSize = sizeof(err);
-#endif
-
 
 #ifdef WIN32
   /*
@@ -431,12 +442,24 @@ static bool verifyconnect(curl_socket_t sockfd, int *error)
    *
    *    Someone got to verify this on Win-NT 4.0, 2000."
    */
+
+#ifdef _WIN32_WCE
+  Sleep(0);
+#else
   SleepEx(0, FALSE);
 #endif
 
+#endif
+
   if( -1 == getsockopt(sockfd, SOL_SOCKET, SO_ERROR,
                        (void *)&err, &errSize))
-    err = Curl_ourerrno();
+    err = Curl_sockerrno();
+
+#ifdef _WIN32_WCE
+  /* Always returns this error, bug in CE? */
+  if(WSAENOPROTOOPT==err)
+    err=0;
+#endif
 
   if ((0 == err) || (EISCONN == err))
     /* we are connected, awesome! */
@@ -449,11 +472,30 @@ static bool verifyconnect(curl_socket_t sockfd, int *error)
 #else
   (void)sockfd;
   if (error)
-    *error = Curl_ourerrno();
+    *error = Curl_sockerrno();
 #endif
   return rc;
 }
 
+CURLcode Curl_store_ip_addr(struct connectdata *conn)
+{
+  char addrbuf[256];
+  Curl_printable_address(conn->ip_addr, addrbuf, sizeof(addrbuf));
+
+  /* save the string */
+  Curl_safefree(conn->ip_addr_str);
+  conn->ip_addr_str = strdup(addrbuf);
+  if(!conn->ip_addr_str)
+    return CURLE_OUT_OF_MEMORY; /* FAIL */
+
+#ifdef PF_INET6
+  if(conn->ip_addr->ai_family == PF_INET6)
+    conn->bits.ipv6 = TRUE;
+#endif
+
+  return CURLE_OK;
+}
+
 /* Used within the multi interface. Try next IP address, return TRUE if no
    more address exists */
 static bool trynextip(struct connectdata *conn,
@@ -463,6 +505,11 @@ static bool trynextip(struct connectdata *conn,
   curl_socket_t sockfd;
   Curl_addrinfo *ai;
 
+  /* first close the failed socket */
+  sclose(conn->sock[sockindex]);
+  conn->sock[sockindex] = CURL_SOCKET_BAD;
+  *connected = FALSE;
+
   if(sockindex != FIRSTSOCKET)
     return TRUE; /* no next */
 
@@ -475,6 +522,8 @@ static bool trynextip(struct connectdata *conn,
       /* store the new socket descriptor */
       conn->sock[sockindex] = sockfd;
       conn->ip_addr = ai;
+
+      Curl_store_ip_addr(conn);
       return FALSE;
     }
     ai = ai->ai_next;
@@ -496,24 +545,25 @@ CURLcode Curl_is_connected(struct connectdata *conn,
   CURLcode code = CURLE_OK;
   curl_socket_t sockfd = conn->sock[sockindex];
   long allow = DEFAULT_CONNECT_TIMEOUT;
+  long allow_total = 0;
   long has_passed;
 
   curlassert(sockindex >= FIRSTSOCKET && sockindex <= SECONDARYSOCKET);
 
   *connected = FALSE; /* a very negative world view is best */
 
   /* Evaluate in milliseconds how much time that has passed */
-  has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.start);
+  has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle);
 
   /* subtract the most strict timeout of the ones */
   if(data->set.timeout && data->set.connecttimeout) {
     if (data->set.timeout < data->set.connecttimeout)
-      allow = data->set.timeout*1000;
+      allow_total = allow = data->set.timeout*1000;
     else
       allow = data->set.connecttimeout*1000;
   }
   else if(data->set.timeout) {
-    allow = data->set.timeout*1000;
+    allow_total = allow = data->set.timeout*1000;
   }
   else if(data->set.connecttimeout) {
     allow = data->set.connecttimeout*1000;
@@ -526,30 +576,45 @@ CURLcode Curl_is_connected(struct connectdata *conn,
   }
   if(conn->bits.tcpconnect) {
     /* we are connected already! */
+    Curl_expire(data, allow_total);
     *connected = TRUE;
     return CURLE_OK;
   }
 
+  Curl_expire(data, allow);
+
   /* check for connect without timeout as we want to return immediately */
   rc = waitconnect(sockfd, 0);
 
   if(WAITCONN_CONNECTED == rc) {
-    if (verifyconnect(sockfd, NULL)) {
+    int error;
+    if (verifyconnect(sockfd, &error)) {
       /* we are connected, awesome! */
       *connected = TRUE;
       return CURLE_OK;
     }
     /* nope, not connected for real */
+    data->state.os_errno = error;
     infof(data, "Connection failed\n");
     if(trynextip(conn, sockindex, connected)) {
       code = CURLE_COULDNT_CONNECT;
     }
   }
   else if(WAITCONN_TIMEOUT != rc) {
+    int error = 0;
+
     /* nope, not connected  */
-    infof(data, "Connection failed\n");
+    if (WAITCONN_FDSET_ERROR == rc) {
+      (void)verifyconnect(sockfd, &error);
+      data->state.os_errno = error;
+      infof(data, "%s\n",Curl_strerror(conn,error));
+    }
+    else
+      infof(data, "Connection failed\n");
+
     if(trynextip(conn, sockindex, connected)) {
-      int error = Curl_ourerrno();
+      error = Curl_sockerrno();
+      data->state.os_errno = error;
       failf(data, "Failed connect to %s:%d; %s",
             conn->host.name, conn->port, Curl_strerror(conn,error));
       code = CURLE_COULDNT_CONNECT;
@@ -569,10 +634,18 @@ static void tcpnodelay(struct connectdata *conn,
 #ifdef TCP_NODELAY
   struct SessionHandle *data= conn->data;
   socklen_t onoff = (socklen_t) data->set.tcp_nodelay;
-  if(setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (void *)&onoff,
+  int proto = IPPROTO_TCP;
+
+#ifdef HAVE_GETPROTOBYNAME
+  struct protoent *pe = getprotobyname("tcp");
+  if (pe)
+    proto = pe->p_proto;
+#endif
+
+  if(setsockopt(sockfd, proto, TCP_NODELAY, (void *)&onoff,
                 sizeof(onoff)) < 0)
     infof(data, "Could not set TCP_NODELAY: %s\n",
-          Curl_strerror(conn, Curl_ourerrno()));
+          Curl_strerror(conn, Curl_sockerrno()));
   else
     infof(data,"TCP_NODELAY set\n");
 #else
@@ -581,21 +654,42 @@ static void tcpnodelay(struct connectdata *conn,
 #endif
 }
 
+#ifdef SO_NOSIGPIPE
+/* The preferred method on Mac OS X (10.2 and later) to prevent SIGPIPEs when
+   sending data to a dead peer (instead of relying on the 4th argument to send
+   being MSG_NOSIGNAL). Possibly also existing and in use on other BSD
+   systems? */
+static void nosigpipe(struct connectdata *conn,
+                      curl_socket_t sockfd)
+{
+  struct SessionHandle *data= conn->data;
+  int onoff = 1;
+  if(setsockopt(sockfd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&onoff,
+                sizeof(onoff)) < 0)
+    infof(data, "Could not set SO_NOSIGPIPE: %s\n",
+          Curl_strerror(conn, Curl_sockerrno()));
+}
+#else
+#define nosigpipe(x,y)
+#endif
+
 /* singleipconnect() connects to the given IP only, and it may return without
    having connected if used from the multi interface. */
 static curl_socket_t
 singleipconnect(struct connectdata *conn,
-                Curl_addrinfo *ai,
+                const Curl_addrinfo *ai,
                 long timeout_ms,
                 bool *connected)
 {
   char addr_buf[128];
   int rc;
   int error;
-  bool conected;
+  bool isconnected;
   struct SessionHandle *data = conn->data;
-  curl_socket_t sockfd = socket(ai->ai_family, ai->ai_socktype,
-                                ai->ai_protocol);
+  curl_socket_t sockfd;
+  CURLcode res;
+
+  sockfd = socket(ai->ai_family, conn->socktype, ai->ai_protocol);
   if (sockfd == CURL_SOCKET_BAD)
     return CURL_SOCKET_BAD;
 
@@ -607,21 +701,37 @@ singleipconnect(struct connectdata *conn,
   if(data->set.tcp_nodelay)
     tcpnodelay(conn, sockfd);
 
-  if(conn->data->set.device) {
-    /* user selected to bind the outgoing socket to a specified "device"
-       before doing connect */
-    CURLcode res = bindlocal(conn, sockfd);
-    if(res)
-      return res;
+  nosigpipe(conn, sockfd);
+
+  if(data->set.fsockopt) {
+    /* activate callback for setting socket options */
+    error = data->set.fsockopt(data->set.sockopt_client,
+                               sockfd,
+                               CURLSOCKTYPE_IPCXN);
+    if (error) {
+      sclose(sockfd); /* close the socket and bail out */
+      return CURL_SOCKET_BAD;
+    }
+  }
+
+  /* possibly bind the local end to an IP, interface or port */
+  res = bindlocal(conn, sockfd);
+  if(res) {
+    sclose(sockfd); /* close socket and bail out */
+    return CURL_SOCKET_BAD;
   }
 
   /* set socket non-blocking */
   Curl_nonblock(sockfd, TRUE);
 
-  rc = connect(sockfd, ai->ai_addr, ai->ai_addrlen);
+  /* Connect TCP sockets, bind UDP */
+  if(conn->socktype == SOCK_STREAM)
+    rc = connect(sockfd, ai->ai_addr, ai->ai_addrlen);
+  else
+    rc = 0;
 
   if(-1 == rc) {
-    error = Curl_ourerrno();
+    error = Curl_sockerrno();
 
     switch (error) {
     case EINPROGRESS:
@@ -639,6 +749,7 @@ singleipconnect(struct connectdata *conn,
       /* unknown error, fallthrough and try another address! */
       failf(data, "Failed to connect to %s: %s",
             addr_buf, Curl_strerror(conn,error));
+      data->state.os_errno = error;
       break;
     }
   }
@@ -651,18 +762,20 @@ singleipconnect(struct connectdata *conn,
     return sockfd;
   }
 
-  conected = verifyconnect(sockfd, &error);
+  isconnected = verifyconnect(sockfd, &error);
 
-  if(!rc && conected) {
+  if(!rc && isconnected) {
     /* we are connected, awesome! */
     *connected = TRUE; /* this is a true connect */
     infof(data, "connected\n");
     return sockfd;
   }
   else if(WAITCONN_TIMEOUT == rc)
     infof(data, "Timeout\n");
-  else
+  else {
+    data->state.os_errno = error;
     infof(data, "%s\n", Curl_strerror(conn, error));
+  }
 
   /* connect failed or timed out */
   sclose(sockfd);
@@ -677,7 +790,7 @@ singleipconnect(struct connectdata *conn,
  */
 
 CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
-                          struct Curl_dns_entry *remotehost, /* use this one */
+                          const struct Curl_dns_entry *remotehost, /* use this one */
                           curl_socket_t *sockconn,   /* the connected socket */
                           Curl_addrinfo **addr,      /* the one we used */
                           bool *connected)           /* really connected? */
@@ -704,7 +817,7 @@ CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
     long has_passed;
 
     /* Evaluate in milliseconds how much time that has passed */
-    has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.start);
+    has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle);
 
 #ifndef min
 #define min(a, b)   ((a) < (b) ? (a) : (b))
@@ -731,6 +844,7 @@ CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
       return CURLE_OPERATION_TIMEOUTED;
     }
   }
+  Curl_expire(data, timeout_ms);
 
   /* Max time for each address */
   num_addr = Curl_num_addresses(remotehost->addr);
@@ -744,7 +858,7 @@ CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
 
   if(data->state.used_interface == Curl_if_multi)
     /* don't hang when doing multi */
-    timeout_per_addr = timeout_ms = 0;
+    timeout_per_addr = 0;
 
   /*
    * Connecting with a Curl_addrinfo chain
@@ -771,6 +885,7 @@ CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
   if (sockfd == CURL_SOCKET_BAD) {
     /* no good connect was made */
     *sockconn = CURL_SOCKET_BAD;
+    failf(data, "couldn't connect to host");
     return CURLE_COULDNT_CONNECT;
   }
 
@@ -784,5 +899,7 @@ CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
   if(sockconn)
     *sockconn = sockfd;    /* the socket descriptor we've connected */
 
+  data->info.numconnects++; /* to track the number of connections made */
+
   return CURLE_OK;
 }