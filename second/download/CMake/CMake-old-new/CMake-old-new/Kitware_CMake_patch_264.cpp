@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2006, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -18,402 +18,453 @@
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
- * $Id$
  ***************************************************************************/
 
-#include "setup.h"
+#include "curl_setup.h"
 
-#ifndef WIN32
-/* headers for non-win32 */
-#ifdef HAVE_SYS_TIME_H
-#include <sys/time.h>
-#endif
-#ifdef HAVE_SYS_TYPES_H
-#include <sys/types.h>
-#endif
-#ifdef HAVE_SYS_SOCKET_H
-#include <sys/socket.h>
-#endif
 #ifdef HAVE_NETINET_IN_H
 #include <netinet/in.h> /* <netinet/tcp.h> may need it */
 #endif
+#ifdef HAVE_SYS_UN_H
+#include <sys/un.h> /* for sockaddr_un */
+#endif
 #ifdef HAVE_NETINET_TCP_H
 #include <netinet/tcp.h> /* for TCP_NODELAY */
 #endif
 #ifdef HAVE_SYS_IOCTL_H
 #include <sys/ioctl.h>
 #endif
-#ifdef HAVE_UNISTD_H
-#include <unistd.h>
-#endif
 #ifdef HAVE_NETDB_H
 #include <netdb.h>
 #endif
 #ifdef HAVE_FCNTL_H
 #include <fcntl.h>
 #endif
-#ifdef HAVE_NETINET_IN_H
-#include <netinet/in.h>
-#endif
 #ifdef HAVE_ARPA_INET_H
 #include <arpa/inet.h>
 #endif
-#ifdef HAVE_STDLIB_H
-#include <stdlib.h> /* required for free() prototype, without it, this crashes
-                       on macos 68K */
-#endif
-#if (defined(HAVE_FIONBIO) && defined(__NOVELL_LIBC__))
+
+#if (defined(HAVE_IOCTL_FIONBIO) && defined(NETWARE))
 #include <sys/filio.h>
 #endif
-#if (defined(NETWARE) && defined(__NOVELL_LIBC__))
+#ifdef NETWARE
 #undef in_addr_t
 #define in_addr_t unsigned long
 #endif
-#ifdef VMS
+#ifdef __VMS
 #include <in.h>
 #include <inet.h>
 #endif
 
-#endif
-#include <stdio.h>
-#include <errno.h>
-#include <string.h>
-
-#ifndef TRUE
-#define TRUE 1
-#define FALSE 0
-#endif
-
-#ifdef USE_WINSOCK
-#define EINPROGRESS WSAEINPROGRESS
-#define EWOULDBLOCK WSAEWOULDBLOCK
-#define EISCONN     WSAEISCONN
-#define ENOTSOCK    WSAENOTSOCK
-#define ECONNREFUSED WSAECONNREFUSED
-#endif
+#define _MPRINTF_REPLACE /* use our functions only */
+#include <curl/mprintf.h>
 
 #include "urldata.h"
 #include "sendf.h"
 #include "if2ip.h"
 #include "strerror.h"
 #include "connect.h"
-#include "memory.h"
+#include "curl_memory.h"
 #include "select.h"
 #include "url.h" /* for Curl_safefree() */
 #include "multiif.h"
 #include "sockaddr.h" /* required for Curl_sockaddr_storage */
 #include "inet_ntop.h"
+#include "inet_pton.h"
+#include "vtls/vtls.h" /* for Curl_ssl_check_cxn() */
+#include "progress.h"
+#include "warnless.h"
+#include "conncache.h"
+#include "multihandle.h"
 
 /* The last #include file should be: */
 #include "memdebug.h"
 
-static bool verifyconnect(curl_socket_t sockfd, int *error);
+#ifdef __SYMBIAN32__
+/* This isn't actually supported under Symbian OS */
+#undef SO_NOSIGPIPE
+#endif
 
-static curl_socket_t
-singleipconnect(struct connectdata *conn,
-                const Curl_addrinfo *ai, /* start connecting to this */
-                long timeout_ms,
-                bool *connected);
+static bool verifyconnect(curl_socket_t sockfd, int *error);
 
-/*
- * Curl_sockerrno() returns the *socket-related* errno (or equivalent) on this
- * platform to hide platform specific for the function that calls this.
- */
-int Curl_sockerrno(void)
-{
-#ifdef USE_WINSOCK
-  return (int)WSAGetLastError();
+#if defined(__DragonFly__) || defined(HAVE_WINSOCK_H)
+/* DragonFlyBSD and Windows use millisecond units */
+#define KEEPALIVE_FACTOR(x) (x *= 1000)
 #else
-  return errno;
+#define KEEPALIVE_FACTOR(x)
 #endif
-}
 
-/*
- * Curl_nonblock() set the given socket to either blocking or non-blocking
- * mode based on the 'nonblock' boolean argument. This function is highly
- * portable.
- */
-int Curl_nonblock(curl_socket_t sockfd,    /* operate on this */
-                  int nonblock   /* TRUE or FALSE */)
-{
-#undef SETBLOCK
-#define SETBLOCK 0
-#ifdef HAVE_O_NONBLOCK
-  /* most recent unix versions */
-  int flags;
-
-  flags = fcntl(sockfd, F_GETFL, 0);
-  if (TRUE == nonblock)
-    return fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
-  else
-    return fcntl(sockfd, F_SETFL, flags & (~O_NONBLOCK));
-#undef SETBLOCK
-#define SETBLOCK 1
-#endif
-
-#if defined(HAVE_FIONBIO) && (SETBLOCK == 0)
-  /* older unix versions */
-  int flags;
+#if defined(HAVE_WINSOCK2_H) && !defined(SIO_KEEPALIVE_VALS)
+#define SIO_KEEPALIVE_VALS    _WSAIOW(IOC_VENDOR,4)
 
-  flags = nonblock;
-  return ioctl(sockfd, FIONBIO, &flags);
-#undef SETBLOCK
-#define SETBLOCK 2
+struct tcp_keepalive {
+  u_long onoff;
+  u_long keepalivetime;
+  u_long keepaliveinterval;
+};
 #endif
 
-#if defined(HAVE_IOCTLSOCKET) && (SETBLOCK == 0)
-  /* Windows? */
-  unsigned long flags;
-  flags = nonblock;
+static void
+tcpkeepalive(struct SessionHandle *data,
+             curl_socket_t sockfd)
+{
+  int optval = data->set.tcp_keepalive?1:0;
 
-  return ioctlsocket(sockfd, FIONBIO, &flags);
-#undef SETBLOCK
-#define SETBLOCK 3
+  /* only set IDLE and INTVL if setting KEEPALIVE is successful */
+  if(setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE,
+        (void *)&optval, sizeof(optval)) < 0) {
+    infof(data, "Failed to set SO_KEEPALIVE on fd %d\n", sockfd);
+  }
+  else {
+#if defined(SIO_KEEPALIVE_VALS)
+    struct tcp_keepalive vals;
+    DWORD dummy;
+    vals.onoff = 1;
+    optval = curlx_sltosi(data->set.tcp_keepidle);
+    KEEPALIVE_FACTOR(optval);
+    vals.keepalivetime = optval;
+    optval = curlx_sltosi(data->set.tcp_keepintvl);
+    KEEPALIVE_FACTOR(optval);
+    vals.keepaliveinterval = optval;
+    if(WSAIoctl(sockfd, SIO_KEEPALIVE_VALS, (LPVOID) &vals, sizeof(vals),
+                NULL, 0, &dummy, NULL, NULL) != 0) {
+      infof(data, "Failed to set SIO_KEEPALIVE_VALS on fd %d: %d\n",
+            (int)sockfd, WSAGetLastError());
+    }
+#else
+#ifdef TCP_KEEPIDLE
+    optval = curlx_sltosi(data->set.tcp_keepidle);
+    KEEPALIVE_FACTOR(optval);
+    if(setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE,
+          (void *)&optval, sizeof(optval)) < 0) {
+      infof(data, "Failed to set TCP_KEEPIDLE on fd %d\n", sockfd);
+    }
 #endif
-
-#if defined(HAVE_IOCTLSOCKET_CASE) && (SETBLOCK == 0)
-  /* presumably for Amiga */
-  return IoctlSocket(sockfd, FIONBIO, (long)nonblock);
-#undef SETBLOCK
-#define SETBLOCK 4
+#ifdef TCP_KEEPINTVL
+    optval = curlx_sltosi(data->set.tcp_keepintvl);
+    KEEPALIVE_FACTOR(optval);
+    if(setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPINTVL,
+          (void *)&optval, sizeof(optval)) < 0) {
+      infof(data, "Failed to set TCP_KEEPINTVL on fd %d\n", sockfd);
+    }
 #endif
-
-#if defined(HAVE_SO_NONBLOCK) && (SETBLOCK == 0)
-  /* BeOS */
-  long b = nonblock ? 1 : 0;
-  return setsockopt(sockfd, SOL_SOCKET, SO_NONBLOCK, &b, sizeof(b));
-#undef SETBLOCK
-#define SETBLOCK 5
+#ifdef TCP_KEEPALIVE
+    /* Mac OS X style */
+    optval = curlx_sltosi(data->set.tcp_keepidle);
+    KEEPALIVE_FACTOR(optval);
+    if(setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPALIVE,
+          (void *)&optval, sizeof(optval)) < 0) {
+      infof(data, "Failed to set TCP_KEEPALIVE on fd %d\n", sockfd);
+    }
 #endif
-
-#ifdef HAVE_DISABLED_NONBLOCKING
-  return 0; /* returns success */
-#undef SETBLOCK
-#define SETBLOCK 6
-#endif
-
-#if (SETBLOCK == 0)
-#error "no non-blocking method was found/used/set"
 #endif
+  }
 }
 
+static CURLcode
+singleipconnect(struct connectdata *conn,
+                const Curl_addrinfo *ai, /* start connecting to this */
+                curl_socket_t *sock);
+
 /*
- * waitconnect() waits for a TCP connect on the given socket for the specified
- * number if milliseconds. It returns:
- * 0    fine connect
- * -1   select() error
- * 1    select() timeout
- * 2    select() returned with an error condition fd_set
+ * Curl_timeleft() returns the amount of milliseconds left allowed for the
+ * transfer/connection. If the value is negative, the timeout time has already
+ * elapsed.
+ *
+ * The start time is stored in progress.t_startsingle - as set with
+ * Curl_pgrsTime(..., TIMER_STARTSINGLE);
+ *
+ * If 'nowp' is non-NULL, it points to the current time.
+ * 'duringconnect' is FALSE if not during a connect, as then of course the
+ * connect timeout is not taken into account!
+ *
+ * @unittest: 1303
  */
-
-#define WAITCONN_CONNECTED     0
-#define WAITCONN_SELECT_ERROR -1
-#define WAITCONN_TIMEOUT       1
-#define WAITCONN_FDSET_ERROR   2
-
-static
-int waitconnect(curl_socket_t sockfd, /* socket */
-                long timeout_msec)
+long Curl_timeleft(struct SessionHandle *data,
+                   struct timeval *nowp,
+                   bool duringconnect)
 {
-  int rc;
-#ifdef mpeix
-  /* Call this function once now, and ignore the results. We do this to
-     "clear" the error state on the socket so that we can later read it
-     reliably. This is reported necessary on the MPE/iX operating system. */
-  (void)verifyconnect(sockfd, NULL);
-#endif
-
-  /* now select() until we get connect or timeout */
-  rc = Curl_select(CURL_SOCKET_BAD, sockfd, (int)timeout_msec);
-  if(-1 == rc)
-    /* error, no connect here, try next */
-    return WAITCONN_SELECT_ERROR;
+  int timeout_set = 0;
+  long timeout_ms = duringconnect?DEFAULT_CONNECT_TIMEOUT:0;
+  struct timeval now;
+
+  /* if a timeout is set, use the most restrictive one */
+
+  if(data->set.timeout > 0)
+    timeout_set |= 1;
+  if(duringconnect && (data->set.connecttimeout > 0))
+    timeout_set |= 2;
+
+  switch (timeout_set) {
+  case 1:
+    timeout_ms = data->set.timeout;
+    break;
+  case 2:
+    timeout_ms = data->set.connecttimeout;
+    break;
+  case 3:
+    if(data->set.timeout < data->set.connecttimeout)
+      timeout_ms = data->set.timeout;
+    else
+      timeout_ms = data->set.connecttimeout;
+    break;
+  default:
+    /* use the default */
+    if(!duringconnect)
+      /* if we're not during connect, there's no default timeout so if we're
+         at zero we better just return zero and not make it a negative number
+         by the math below */
+      return 0;
+    break;
+  }
 
-  else if(0 == rc)
-    /* timeout, no connect today */
-    return WAITCONN_TIMEOUT;
+  if(!nowp) {
+    now = Curl_tvnow();
+    nowp = &now;
+  }
 
-  if(rc & CSELECT_ERR)
-    /* error condition caught */
-    return WAITCONN_FDSET_ERROR;
+  /* subtract elapsed time */
+  if(duringconnect)
+    /* since this most recent connect started */
+    timeout_ms -= Curl_tvdiff(*nowp, data->progress.t_startsingle);
+  else
+    /* since the entire operation started */
+    timeout_ms -= Curl_tvdiff(*nowp, data->progress.t_startop);
+  if(!timeout_ms)
+    /* avoid returning 0 as that means no timeout! */
+    return -1;
 
-  /* we have a connect! */
-  return WAITCONN_CONNECTED;
+  return timeout_ms;
 }
 
 static CURLcode bindlocal(struct connectdata *conn,
-                          curl_socket_t sockfd)
+                          curl_socket_t sockfd, int af)
 {
   struct SessionHandle *data = conn->data;
-  struct sockaddr_in me;
-  struct sockaddr *sock = NULL;  /* bind to this address */
-  socklen_t socksize; /* size of the data sock points to */
+
+  struct Curl_sockaddr_storage sa;
+  struct sockaddr *sock = (struct sockaddr *)&sa;  /* bind to this address */
+  curl_socklen_t sizeof_sa = 0; /* size of the data sock points to */
+  struct sockaddr_in *si4 = (struct sockaddr_in *)&sa;
+#ifdef ENABLE_IPV6
+  struct sockaddr_in6 *si6 = (struct sockaddr_in6 *)&sa;
+#endif
+
+  struct Curl_dns_entry *h=NULL;
   unsigned short port = data->set.localport; /* use this port number, 0 for
                                                 "random" */
   /* how many port numbers to try to bind to, increasing one at a time */
   int portnum = data->set.localportrange;
+  const char *dev = data->set.str[STRING_DEVICE];
+  int error;
+  char myhost[256] = "";
+  int done = 0; /* -1 for error, 1 for address found */
+  bool is_interface = FALSE;
+  bool is_host = FALSE;
+  static const char *if_prefix = "if!";
+  static const char *host_prefix = "host!";
 
   /*************************************************************
    * Select device to bind socket to
    *************************************************************/
-  if (data->set.device && (strlen(data->set.device)<255) ) {
-    struct Curl_dns_entry *h=NULL;
-    char myhost[256] = "";
-    in_addr_t in;
-    int rc;
-    bool was_iface = FALSE;
-
-    /* First check if the given name is an IP address */
-    in=inet_addr(data->set.device);
-
-    if((in == CURL_INADDR_NONE) &&
-       Curl_if2ip(data->set.device, myhost, sizeof(myhost))) {
-      /*
-       * We now have the numerical IPv4-style x.y.z.w in the 'myhost' buffer
-       */
-      rc = Curl_resolv(conn, myhost, 0, &h);
-      if(rc == CURLRESOLV_PENDING)
-        (void)Curl_wait_for_resolv(conn, &h);
+  if(!dev && !port)
+    /* no local kind of binding was requested */
+    return CURLE_OK;
 
-      if(h) {
-        was_iface = TRUE;
-        Curl_resolv_unlock(data, h);
-      }
+  memset(&sa, 0, sizeof(struct Curl_sockaddr_storage));
+
+  if(dev && (strlen(dev)<255) ) {
+    if(strncmp(if_prefix, dev, strlen(if_prefix)) == 0) {
+      dev += strlen(if_prefix);
+      is_interface = TRUE;
     }
+    else if(strncmp(host_prefix, dev, strlen(host_prefix)) == 0) {
+      dev += strlen(host_prefix);
+      is_host = TRUE;
+    }
+
+    /* interface */
+    if(!is_host) {
+      switch(Curl_if2ip(af, conn->scope, dev, myhost, sizeof(myhost))) {
+        case IF2IP_NOT_FOUND:
+          if(is_interface) {
+            /* Do not fall back to treating it as a host name */
+            failf(data, "Couldn't bind to interface '%s'", dev);
+            return CURLE_INTERFACE_FAILED;
+          }
+          break;
+        case IF2IP_AF_NOT_SUPPORTED:
+          /* Signal the caller to try another address family if available */
+          return CURLE_UNSUPPORTED_PROTOCOL;
+        case IF2IP_FOUND:
+          is_interface = TRUE;
+          /*
+           * We now have the numerical IP address in the 'myhost' buffer
+           */
+          infof(data, "Local Interface %s is ip %s using address family %i\n",
+                dev, myhost, af);
+          done = 1;
 
-    if(!was_iface) {
+#ifdef SO_BINDTODEVICE
+          /* I am not sure any other OSs than Linux that provide this feature,
+           * and at the least I cannot test. --Ben
+           *
+           * This feature allows one to tightly bind the local socket to a
+           * particular interface.  This will force even requests to other
+           * local interfaces to go out the external interface.
+           *
+           *
+           * Only bind to the interface when specified as interface, not just
+           * as a hostname or ip address.
+           */
+          if(setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
+                        dev, (curl_socklen_t)strlen(dev)+1) != 0) {
+            error = SOCKERRNO;
+            infof(data, "SO_BINDTODEVICE %s failed with errno %d: %s;"
+                  " will do regular bind\n",
+                  dev, error, Curl_strerror(conn, error));
+            /* This is typically "errno 1, error: Operation not permitted" if
+               you're not running as root or another suitable privileged
+               user */
+          }
+#endif
+          break;
+      }
+    }
+    if(!is_interface) {
       /*
        * This was not an interface, resolve the name as a host name
        * or IP number
+       *
+       * Temporarily force name resolution to use only the address type
+       * of the connection. The resolve functions should really be changed
+       * to take a type parameter instead.
        */
-      rc = Curl_resolv(conn, data->set.device, 0, &h);
+      long ipver = conn->ip_version;
+      int rc;
+
+      if(af == AF_INET)
+        conn->ip_version = CURL_IPRESOLVE_V4;
+#ifdef ENABLE_IPV6
+      else if(af == AF_INET6)
+        conn->ip_version = CURL_IPRESOLVE_V6;
+#endif
+
+      rc = Curl_resolv(conn, dev, 0, &h);
       if(rc == CURLRESOLV_PENDING)
-        (void)Curl_wait_for_resolv(conn, &h);
+        (void)Curl_resolver_wait_resolv(conn, &h);
+      conn->ip_version = ipver;
 
       if(h) {
-        if(in == CURL_INADDR_NONE)
-          /* convert the resolved address, sizeof myhost >= INET_ADDRSTRLEN */
-          Curl_inet_ntop(h->addr->ai_addr->sa_family,
-                         &((struct sockaddr_in*)h->addr->ai_addr)->sin_addr,
-                         myhost, sizeof myhost);
-        else
-          /* we know data->set.device is shorter than the myhost array */
-          strcpy(myhost, data->set.device);
+        /* convert the resolved address, sizeof myhost >= INET_ADDRSTRLEN */
+        Curl_printable_address(h->addr, myhost, sizeof(myhost));
+        infof(data, "Name '%s' family %i resolved to '%s' family %i\n",
+              dev, af, myhost, h->addr->ai_family);
         Curl_resolv_unlock(data, h);
+        done = 1;
+      }
+      else {
+        /*
+         * provided dev was no interface (or interfaces are not supported
+         * e.g. solaris) no ip address and no domain we fail here
+         */
+        done = -1;
       }
     }
 
-    if(! *myhost) {
-      /* need to fix this
-         h=Curl_gethost(data,
-         getmyhost(*myhost,sizeof(myhost)),
-         hostent_buf,
-         sizeof(hostent_buf));
-      */
-      failf(data, "Couldn't bind to '%s'", data->set.device);
-      return CURLE_HTTP_PORT_FAILED;
-    }
-
-    infof(data, "Bind local address to %s\n", myhost);
-
-#ifdef SO_BINDTODEVICE
-    /* I am not sure any other OSs than Linux that provide this feature, and
-     * at the least I cannot test. --Ben
-     *
-     * This feature allows one to tightly bind the local socket to a
-     * particular interface.  This will force even requests to other local
-     * interfaces to go out the external interface.
-     *
-     */
-    if (was_iface) {
-      /* Only bind to the interface when specified as interface, not just as a
-       * hostname or ip address.
-       */
-      if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
-                     data->set.device, strlen(data->set.device)+1) != 0) {
-        /* printf("Failed to BINDTODEVICE, socket: %d  device: %s error: %s\n",
-           sockfd, data->set.device, Curl_strerror(Curl_sockerrno())); */
-        infof(data, "SO_BINDTODEVICE %s failed\n",
-              data->set.device);
-        /* This is typically "errno 1, error: Operation not permitted" if
-           you're not running as root or another suitable privileged user */
+    if(done > 0) {
+#ifdef ENABLE_IPV6
+      /* ipv6 address */
+      if(af == AF_INET6) {
+#ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
+        char *scope_ptr = strchr(myhost, '%');
+        if(scope_ptr)
+          *(scope_ptr++) = 0;
+#endif
+        if(Curl_inet_pton(AF_INET6, myhost, &si6->sin6_addr) > 0) {
+          si6->sin6_family = AF_INET6;
+          si6->sin6_port = htons(port);
+#ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
+          if(scope_ptr)
+            /* The "myhost" string either comes from Curl_if2ip or from
+               Curl_printable_address. The latter returns only numeric scope
+               IDs and the former returns none at all.  So the scope ID, if
+               present, is known to be numeric */
+            si6->sin6_scope_id = atoi(scope_ptr);
+#endif
+        }
+        sizeof_sa = sizeof(struct sockaddr_in6);
       }
-    }
+      else
 #endif
-
-    in=inet_addr(myhost);
-    if (CURL_INADDR_NONE == in) {
-      failf(data,"couldn't find my own IP address (%s)", myhost);
-      return CURLE_HTTP_PORT_FAILED;
-    } /* end of inet_addr */
-
-    if ( h ) {
-      Curl_addrinfo *addr = h->addr;
-      sock = addr->ai_addr;
-      socksize = addr->ai_addrlen;
+      /* ipv4 address */
+      if((af == AF_INET) &&
+         (Curl_inet_pton(AF_INET, myhost, &si4->sin_addr) > 0)) {
+        si4->sin_family = AF_INET;
+        si4->sin_port = htons(port);
+        sizeof_sa = sizeof(struct sockaddr_in);
+      }
     }
-    else
-      return CURLE_HTTP_PORT_FAILED;
-
-  }
-  else if(port) {
-    /* if a local port number is requested but no local IP, extract the
-       address from the socket */
-    memset(&me, 0, sizeof(struct sockaddr));
-    me.sin_family = AF_INET;
-    me.sin_addr.s_addr = INADDR_ANY;
-
-    sock = (struct sockaddr *)&me;
-    socksize = sizeof(struct sockaddr);
 
+    if(done < 1) {
+      failf(data, "Couldn't bind to '%s'", dev);
+      return CURLE_INTERFACE_FAILED;
+    }
   }
-  else
-    /* no local kind of binding was requested */
-    return CURLE_OK;
-
-  do {
-
-    /* Set port number to bind to, 0 makes the system pick one */
-    if(sock->sa_family == AF_INET)
-      ((struct sockaddr_in *)sock)->sin_port = htons(port);
+  else {
+    /* no device was given, prepare sa to match af's needs */
 #ifdef ENABLE_IPV6
+    if(af == AF_INET6) {
+      si6->sin6_family = AF_INET6;
+      si6->sin6_port = htons(port);
+      sizeof_sa = sizeof(struct sockaddr_in6);
+    }
     else
-      ((struct sockaddr_in6 *)sock)->sin6_port = htons(port);
 #endif
+    if(af == AF_INET) {
+      si4->sin_family = AF_INET;
+      si4->sin_port = htons(port);
+      sizeof_sa = sizeof(struct sockaddr_in);
+    }
+  }
 
-    if( bind(sockfd, sock, socksize) >= 0) {
+  for(;;) {
+    if(bind(sockfd, sock, sizeof_sa) >= 0) {
       /* we succeeded to bind */
       struct Curl_sockaddr_storage add;
-      socklen_t size;
-
-      size = sizeof(add);
+      curl_socklen_t size = sizeof(add);
+      memset(&add, 0, sizeof(struct Curl_sockaddr_storage));
       if(getsockname(sockfd, (struct sockaddr *) &add, &size) < 0) {
-        failf(data, "getsockname() failed");
-        return CURLE_HTTP_PORT_FAILED;
+        data->state.os_errno = error = SOCKERRNO;
+        failf(data, "getsockname() failed with errno %d: %s",
+              error, Curl_strerror(conn, error));
+        return CURLE_INTERFACE_FAILED;
       }
-      /* We re-use/clobber the port variable here below */
-      if(((struct sockaddr *)&add)->sa_family == AF_INET)
-        port = ntohs(((struct sockaddr_in *)&add)->sin_port);
-#ifdef ENABLE_IPV6
-      else
-        port = ntohs(((struct sockaddr_in6 *)&add)->sin6_port);
-#endif
-      infof(data, "Local port: %d\n", port);
+      infof(data, "Local port: %hu\n", port);
+      conn->bits.bound = TRUE;
       return CURLE_OK;
     }
+
     if(--portnum > 0) {
-      infof(data, "Bind to local port %d failed, trying next\n", port);
+      infof(data, "Bind to local port %hu failed, trying next\n", port);
       port++; /* try next port */
+      /* We re-use/clobber the port variable here below */
+      if(sock->sa_family == AF_INET)
+        si4->sin_port = ntohs(port);
+#ifdef ENABLE_IPV6
+      else
+        si6->sin6_port = ntohs(port);
+#endif
     }
     else
       break;
-  } while(1);
+  }
 
-  data->state.os_errno = Curl_sockerrno();
-  failf(data, "bind failure: %s",
-        Curl_strerror(conn, data->state.os_errno));
-  return CURLE_HTTP_PORT_FAILED;
+  data->state.os_errno = error = SOCKERRNO;
+  failf(data, "bind failed with errno %d: %s",
+        error, Curl_strerror(conn, error));
 
+  return CURLE_INTERFACE_FAILED;
 }
 
 /*
@@ -424,7 +475,7 @@ static bool verifyconnect(curl_socket_t sockfd, int *error)
   bool rc = TRUE;
 #ifdef SO_ERROR
   int err = 0;
-  socklen_t errSize = sizeof(err);
+  curl_socklen_t errSize = sizeof(err);
 
 #ifdef WIN32
   /*
@@ -451,179 +502,349 @@ static bool verifyconnect(curl_socket_t sockfd, int *error)
 
 #endif
 
-  if( -1 == getsockopt(sockfd, SOL_SOCKET, SO_ERROR,
-                       (void *)&err, &errSize))
-    err = Curl_sockerrno();
-
+  if(0 != getsockopt(sockfd, SOL_SOCKET, SO_ERROR, (void *)&err, &errSize))
+    err = SOCKERRNO;
 #ifdef _WIN32_WCE
-  /* Always returns this error, bug in CE? */
-  if(WSAENOPROTOOPT==err)
-    err=0;
+  /* Old WinCE versions don't support SO_ERROR */
+  if(WSAENOPROTOOPT == err) {
+    SET_SOCKERRNO(0);
+    err = 0;
+  }
 #endif
-
-  if ((0 == err) || (EISCONN == err))
+#ifdef __minix
+  /* Minix 3.1.x doesn't support getsockopt on UDP sockets */
+  if(EBADIOCTL == err) {
+    SET_SOCKERRNO(0);
+    err = 0;
+  }
+#endif
+  if((0 == err) || (EISCONN == err))
     /* we are connected, awesome! */
     rc = TRUE;
   else
     /* This wasn't a successful connect */
     rc = FALSE;
-  if (error)
+  if(error)
     *error = err;
 #else
   (void)sockfd;
-  if (error)
-    *error = Curl_sockerrno();
+  if(error)
+    *error = SOCKERRNO;
 #endif
   return rc;
 }
 
-CURLcode Curl_store_ip_addr(struct connectdata *conn)
+/* Used within the multi interface. Try next IP address, return TRUE if no
+   more address exists or error */
+static CURLcode trynextip(struct connectdata *conn,
+                          int sockindex,
+                          int tempindex)
 {
-  char addrbuf[256];
-  Curl_printable_address(conn->ip_addr, addrbuf, sizeof(addrbuf));
+  CURLcode rc = CURLE_COULDNT_CONNECT;
+
+  /* First clean up after the failed socket.
+     Don't close it yet to ensure that the next IP's socket gets a different
+     file descriptor, which can prevent bugs when the curl_multi_socket_action
+     interface is used with certain select() replacements such as kqueue. */
+  curl_socket_t fd_to_close = conn->tempsock[tempindex];
+  conn->tempsock[tempindex] = CURL_SOCKET_BAD;
+
+  if(sockindex == FIRSTSOCKET) {
+    Curl_addrinfo *ai = NULL;
+    int family = AF_UNSPEC;
+
+    if(conn->tempaddr[tempindex]) {
+      /* find next address in the same protocol family */
+      family = conn->tempaddr[tempindex]->ai_family;
+      ai = conn->tempaddr[tempindex]->ai_next;
+    }
+    else if(conn->tempaddr[0]) {
+      /* happy eyeballs - try the other protocol family */
+      int firstfamily = conn->tempaddr[0]->ai_family;
+#ifdef ENABLE_IPV6
+      family = (firstfamily == AF_INET) ? AF_INET6 : AF_INET;
+#else
+      family = firstfamily;
+#endif
+      ai = conn->tempaddr[0]->ai_next;
+    }
+
+    while(ai) {
+      while(ai && ai->ai_family != family)
+        ai = ai->ai_next;
+
+      if(ai) {
+        rc = singleipconnect(conn, ai, &conn->tempsock[tempindex]);
+        if(rc == CURLE_COULDNT_CONNECT) {
+          ai = ai->ai_next;
+          continue;
+        }
+        conn->tempaddr[tempindex] = ai;
+      }
+      break;
+    }
+  }
+
+  if(fd_to_close != CURL_SOCKET_BAD)
+    Curl_closesocket(conn, fd_to_close);
+
+  return rc;
+}
+
+/* Copies connection info into the session handle to make it available
+   when the session handle is no longer associated with a connection. */
+void Curl_persistconninfo(struct connectdata *conn)
+{
+  memcpy(conn->data->info.conn_primary_ip, conn->primary_ip, MAX_IPADR_LEN);
+  memcpy(conn->data->info.conn_local_ip, conn->local_ip, MAX_IPADR_LEN);
+  conn->data->info.conn_primary_port = conn->primary_port;
+  conn->data->info.conn_local_port = conn->local_port;
+}
 
-  /* save the string */
-  Curl_safefree(conn->ip_addr_str);
-  conn->ip_addr_str = strdup(addrbuf);
-  if(!conn->ip_addr_str)
-    return CURLE_OUT_OF_MEMORY; /* FAIL */
+/* retrieves ip address and port from a sockaddr structure */
+static bool getaddressinfo(struct sockaddr* sa, char* addr,
+                           long* port)
+{
+  unsigned short us_port;
+  struct sockaddr_in* si = NULL;
+#ifdef ENABLE_IPV6
+  struct sockaddr_in6* si6 = NULL;
+#endif
+#if defined(HAVE_SYS_UN_H) && defined(AF_UNIX)
+  struct sockaddr_un* su = NULL;
+#endif
 
-#ifdef PF_INET6
-  if(conn->ip_addr->ai_family == PF_INET6)
-    conn->bits.ipv6 = TRUE;
+  switch (sa->sa_family) {
+    case AF_INET:
+      si = (struct sockaddr_in*) sa;
+      if(Curl_inet_ntop(sa->sa_family, &si->sin_addr,
+                        addr, MAX_IPADR_LEN)) {
+        us_port = ntohs(si->sin_port);
+        *port = us_port;
+        return TRUE;
+      }
+      break;
+#ifdef ENABLE_IPV6
+    case AF_INET6:
+      si6 = (struct sockaddr_in6*)sa;
+      if(Curl_inet_ntop(sa->sa_family, &si6->sin6_addr,
+                        addr, MAX_IPADR_LEN)) {
+        us_port = ntohs(si6->sin6_port);
+        *port = us_port;
+        return TRUE;
+      }
+      break;
 #endif
+#if defined(HAVE_SYS_UN_H) && defined(AF_UNIX)
+    case AF_UNIX:
+      su = (struct sockaddr_un*)sa;
+      snprintf(addr, MAX_IPADR_LEN, "%s", su->sun_path);
+      *port = 0;
+      return TRUE;
+#endif
+    default:
+      break;
+  }
 
-  return CURLE_OK;
+  addr[0] = '\0';
+  *port = 0;
+
+  return FALSE;
 }
 
-/* Used within the multi interface. Try next IP address, return TRUE if no
-   more address exists */
-static bool trynextip(struct connectdata *conn,
-                      int sockindex,
-                      bool *connected)
+/* retrieves the start/end point information of a socket of an established
+   connection */
+void Curl_updateconninfo(struct connectdata *conn, curl_socket_t sockfd)
 {
-  curl_socket_t sockfd;
-  Curl_addrinfo *ai;
+  int error;
+  curl_socklen_t len;
+  struct Curl_sockaddr_storage ssrem;
+  struct Curl_sockaddr_storage ssloc;
+  struct SessionHandle *data = conn->data;
 
-  /* first close the failed socket */
-  sclose(conn->sock[sockindex]);
-  conn->sock[sockindex] = CURL_SOCKET_BAD;
-  *connected = FALSE;
+  if(conn->socktype == SOCK_DGRAM)
+    /* there's no connection! */
+    return;
 
-  if(sockindex != FIRSTSOCKET)
-    return TRUE; /* no next */
+  if(!conn->bits.reuse) {
 
-  /* try the next address */
-  ai = conn->ip_addr->ai_next;
+    len = sizeof(struct Curl_sockaddr_storage);
+    if(getpeername(sockfd, (struct sockaddr*) &ssrem, &len)) {
+      error = SOCKERRNO;
+      failf(data, "getpeername() failed with errno %d: %s",
+            error, Curl_strerror(conn, error));
+      return;
+    }
 
-  while (ai) {
-    sockfd = singleipconnect(conn, ai, 0L, connected);
-    if(sockfd != CURL_SOCKET_BAD) {
-      /* store the new socket descriptor */
-      conn->sock[sockindex] = sockfd;
-      conn->ip_addr = ai;
+    len = sizeof(struct Curl_sockaddr_storage);
+    if(getsockname(sockfd, (struct sockaddr*) &ssloc, &len)) {
+      error = SOCKERRNO;
+      failf(data, "getsockname() failed with errno %d: %s",
+            error, Curl_strerror(conn, error));
+      return;
+    }
 
-      Curl_store_ip_addr(conn);
-      return FALSE;
+    if(!getaddressinfo((struct sockaddr*)&ssrem,
+                        conn->primary_ip, &conn->primary_port)) {
+      error = ERRNO;
+      failf(data, "ssrem inet_ntop() failed with errno %d: %s",
+            error, Curl_strerror(conn, error));
+      return;
     }
-    ai = ai->ai_next;
+    memcpy(conn->ip_addr_str, conn->primary_ip, MAX_IPADR_LEN);
+
+    if(!getaddressinfo((struct sockaddr*)&ssloc,
+                       conn->local_ip, &conn->local_port)) {
+      error = ERRNO;
+      failf(data, "ssloc inet_ntop() failed with errno %d: %s",
+            error, Curl_strerror(conn, error));
+      return;
+    }
+
   }
-  return TRUE;
+
+  /* persist connection info in session handle */
+  Curl_persistconninfo(conn);
 }
 
 /*
- * Curl_is_connected() is used from the multi interface to check if the
- * firstsocket has connected.
+ * Curl_is_connected() checks if the socket has connected.
  */
 
 CURLcode Curl_is_connected(struct connectdata *conn,
                            int sockindex,
                            bool *connected)
 {
-  int rc;
   struct SessionHandle *data = conn->data;
   CURLcode code = CURLE_OK;
-  curl_socket_t sockfd = conn->sock[sockindex];
-  long allow = DEFAULT_CONNECT_TIMEOUT;
-  long allow_total = 0;
-  long has_passed;
+  long allow;
+  int error = 0;
+  struct timeval now;
+  int result;
+  int i;
 
-  curlassert(sockindex >= FIRSTSOCKET && sockindex <= SECONDARYSOCKET);
+  DEBUGASSERT(sockindex >= FIRSTSOCKET && sockindex <= SECONDARYSOCKET);
 
   *connected = FALSE; /* a very negative world view is best */
 
-  /* Evaluate in milliseconds how much time that has passed */
-  has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle);
-
-  /* subtract the most strict timeout of the ones */
-  if(data->set.timeout && data->set.connecttimeout) {
-    if (data->set.timeout < data->set.connecttimeout)
-      allow_total = allow = data->set.timeout*1000;
-    else
-      allow = data->set.connecttimeout*1000;
-  }
-  else if(data->set.timeout) {
-    allow_total = allow = data->set.timeout*1000;
-  }
-  else if(data->set.connecttimeout) {
-    allow = data->set.connecttimeout*1000;
-  }
-
-  if(has_passed > allow ) {
-    /* time-out, bail out, go home */
-    failf(data, "Connection time-out after %ld ms", has_passed);
-    return CURLE_OPERATION_TIMEOUTED;
-  }
-  if(conn->bits.tcpconnect) {
+  if(conn->bits.tcpconnect[sockindex]) {
     /* we are connected already! */
-    Curl_expire(data, allow_total);
     *connected = TRUE;
     return CURLE_OK;
   }
 
-  Curl_expire(data, allow);
+  now = Curl_tvnow();
 
-  /* check for connect without timeout as we want to return immediately */
-  rc = waitconnect(sockfd, 0);
+  /* figure out how long time we have left to connect */
+  allow = Curl_timeleft(data, &now, TRUE);
 
-  if(WAITCONN_CONNECTED == rc) {
-    int error;
-    if (verifyconnect(sockfd, &error)) {
-      /* we are connected, awesome! */
-      *connected = TRUE;
-      return CURLE_OK;
+  if(allow < 0) {
+    /* time-out, bail out, go home */
+    failf(data, "Connection time-out");
+    return CURLE_OPERATION_TIMEDOUT;
+  }
+
+  for(i=0; i<2; i++) {
+    if(conn->tempsock[i] == CURL_SOCKET_BAD)
+      continue;
+
+#ifdef mpeix
+    /* Call this function once now, and ignore the results. We do this to
+       "clear" the error state on the socket so that we can later read it
+       reliably. This is reported necessary on the MPE/iX operating system. */
+    (void)verifyconnect(conn->tempsock[i], NULL);
+#endif
+
+    /* check socket for connect */
+    result = Curl_socket_ready(CURL_SOCKET_BAD, conn->tempsock[i], 0);
+
+    if(result == 0) { /* no connection yet */
+      if(curlx_tvdiff(now, conn->connecttime) >= conn->timeoutms_per_addr) {
+        infof(data, "After %ldms connect time, move on!\n",
+              conn->timeoutms_per_addr);
+        error = ETIMEDOUT;
+      }
+
+      /* should we try another protocol family? */
+      if(i == 0 && conn->tempaddr[1] == NULL &&
+         curlx_tvdiff(now, conn->connecttime) >= HAPPY_EYEBALLS_TIMEOUT) {
+        trynextip(conn, sockindex, 1);
+      }
     }
-    /* nope, not connected for real */
-    data->state.os_errno = error;
-    infof(data, "Connection failed\n");
-    if(trynextip(conn, sockindex, connected)) {
-      code = CURLE_COULDNT_CONNECT;
+    else if(result == CURL_CSELECT_OUT) {
+      if(verifyconnect(conn->tempsock[i], &error)) {
+        /* we are connected with TCP, awesome! */
+        int other = i ^ 1;
+
+        /* use this socket from now on */
+        conn->sock[sockindex] = conn->tempsock[i];
+        conn->ip_addr = conn->tempaddr[i];
+        conn->tempsock[i] = CURL_SOCKET_BAD;
+
+        /* close the other socket, if open */
+        if(conn->tempsock[other] != CURL_SOCKET_BAD) {
+          Curl_closesocket(conn, conn->tempsock[other]);
+          conn->tempsock[other] = CURL_SOCKET_BAD;
+        }
+
+        /* see if we need to do any proxy magic first once we connected */
+        code = Curl_connected_proxy(conn, sockindex);
+        if(code)
+          return code;
+
+        conn->bits.tcpconnect[sockindex] = TRUE;
+
+        *connected = TRUE;
+        if(sockindex == FIRSTSOCKET)
+          Curl_pgrsTime(data, TIMER_CONNECT); /* connect done */
+        Curl_updateconninfo(conn, conn->sock[sockindex]);
+        Curl_verboseconnect(conn);
+
+        return CURLE_OK;
+      }
+      else
+        infof(data, "Connection failed\n");
     }
-  }
-  else if(WAITCONN_TIMEOUT != rc) {
-    int error = 0;
+    else if(result & CURL_CSELECT_ERR)
+      (void)verifyconnect(conn->tempsock[i], &error);
 
-    /* nope, not connected  */
-    if (WAITCONN_FDSET_ERROR == rc) {
-      (void)verifyconnect(sockfd, &error);
+    /*
+     * The connection failed here, we should attempt to connect to the "next
+     * address" for the given host. But first remember the latest error.
+     */
+    if(error) {
+      char ipaddress[MAX_IPADR_LEN];
       data->state.os_errno = error;
-      infof(data, "%s\n",Curl_strerror(conn,error));
+      SET_SOCKERRNO(error);
+      if(conn->tempaddr[i]) {
+        Curl_printable_address(conn->tempaddr[i], ipaddress, MAX_IPADR_LEN);
+        infof(data, "connect to %s port %ld failed: %s\n",
+              ipaddress, conn->port, Curl_strerror(conn, error));
+
+        conn->timeoutms_per_addr = conn->tempaddr[i]->ai_next == NULL ?
+                                   allow : allow / 2;
+
+        code = trynextip(conn, sockindex, i);
+      }
     }
-    else
-      infof(data, "Connection failed\n");
+  }
 
-    if(trynextip(conn, sockindex, connected)) {
-      error = Curl_sockerrno();
-      data->state.os_errno = error;
-      failf(data, "Failed connect to %s:%d; %s",
-            conn->host.name, conn->port, Curl_strerror(conn,error));
-      code = CURLE_COULDNT_CONNECT;
+  if(code) {
+    /* no more addresses to try */
+
+    /* if the first address family runs out of addresses to try before
+       the happy eyeball timeout, go ahead and try the next family now */
+    if(conn->tempaddr[1] == NULL) {
+      int rc;
+      rc = trynextip(conn, sockindex, 1);
+      if(rc == CURLE_OK)
+        return CURLE_OK;
     }
+
+    failf(data, "Failed to connect to %s port %ld: %s",
+          conn->bits.proxy?conn->proxy.name:conn->host.name,
+          conn->port, Curl_strerror(conn, error));
   }
-  /*
-   * If the connection failed here, we should attempt to connect to the "next
-   * address" for the given host.
-   */
 
   return code;
 }
@@ -633,19 +854,26 @@ static void tcpnodelay(struct connectdata *conn,
 {
 #ifdef TCP_NODELAY
   struct SessionHandle *data= conn->data;
-  socklen_t onoff = (socklen_t) data->set.tcp_nodelay;
-  int proto = IPPROTO_TCP;
-
-#ifdef HAVE_GETPROTOBYNAME
+  curl_socklen_t onoff = (curl_socklen_t) data->set.tcp_nodelay;
+  int level = IPPROTO_TCP;
+
+#if 0
+  /* The use of getprotobyname() is disabled since it isn't thread-safe on
+     numerous systems. On these getprotobyname_r() should be used instead, but
+     that exists in at least one 4 arg version and one 5 arg version, and
+     since the proto number rarely changes anyway we now just use the hard
+     coded number. The "proper" fix would need a configure check for the
+     correct function much in the same style the gethostbyname_r versions are
+     detected. */
   struct protoent *pe = getprotobyname("tcp");
-  if (pe)
-    proto = pe->p_proto;
+  if(pe)
+    level = pe->p_proto;
 #endif
 
-  if(setsockopt(sockfd, proto, TCP_NODELAY, (void *)&onoff,
+  if(setsockopt(sockfd, level, TCP_NODELAY, (void *)&onoff,
                 sizeof(onoff)) < 0)
     infof(data, "Could not set TCP_NODELAY: %s\n",
-          Curl_strerror(conn, Curl_sockerrno()));
+          Curl_strerror(conn, SOCKERRNO));
   else
     infof(data,"TCP_NODELAY set\n");
 #else
@@ -667,120 +895,214 @@ static void nosigpipe(struct connectdata *conn,
   if(setsockopt(sockfd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&onoff,
                 sizeof(onoff)) < 0)
     infof(data, "Could not set SO_NOSIGPIPE: %s\n",
-          Curl_strerror(conn, Curl_sockerrno()));
+          Curl_strerror(conn, SOCKERRNO));
 }
 #else
-#define nosigpipe(x,y)
+#define nosigpipe(x,y) Curl_nop_stmt
+#endif
+
+#ifdef USE_WINSOCK
+/* When you run a program that uses the Windows Sockets API, you may
+   experience slow performance when you copy data to a TCP server.
+
+   http://support.microsoft.com/kb/823764
+
+   Work-around: Make the Socket Send Buffer Size Larger Than the Program Send
+   Buffer Size
+
+   The problem described in this knowledge-base is applied only to pre-Vista
+   Windows.  Following function trying to detect OS version and skips
+   SO_SNDBUF adjustment for Windows Vista and above.
+*/
+#define DETECT_OS_NONE 0
+#define DETECT_OS_PREVISTA 1
+#define DETECT_OS_VISTA_OR_LATER 2
+
+void Curl_sndbufset(curl_socket_t sockfd)
+{
+  int val = CURL_MAX_WRITE_SIZE + 32;
+  int curval = 0;
+  int curlen = sizeof(curval);
+  DWORD majorVersion = 6;
+
+  static int detectOsState = DETECT_OS_NONE;
+
+  if(detectOsState == DETECT_OS_NONE) {
+#if !defined(_WIN32_WINNT) || !defined(_WIN32_WINNT_WIN2K) || \
+    (_WIN32_WINNT < _WIN32_WINNT_WIN2K)
+    OSVERSIONINFO osver;
+
+    memset(&osver, 0, sizeof(osver));
+    osver.dwOSVersionInfoSize = sizeof(osver);
+
+    detectOsState = DETECT_OS_PREVISTA;
+    if(GetVersionEx(&osver)) {
+      if(osver.dwMajorVersion >= majorVersion)
+        detectOsState = DETECT_OS_VISTA_OR_LATER;
+    }
+#else
+    ULONGLONG majorVersionMask;
+    OSVERSIONINFOEX osver;
+
+    memset(&osver, 0, sizeof(osver));
+    osver.dwOSVersionInfoSize = sizeof(osver);
+    osver.dwMajorVersion = majorVersion;
+    majorVersionMask = VerSetConditionMask(0, VER_MAJORVERSION,
+                                           VER_GREATER_EQUAL);
+
+    if(VerifyVersionInfo(&osver, VER_MAJORVERSION, majorVersionMask))
+      detectOsState = DETECT_OS_VISTA_OR_LATER;
+    else
+      detectOsState = DETECT_OS_PREVISTA;
+#endif
+  }
+
+  if(detectOsState == DETECT_OS_VISTA_OR_LATER)
+    return;
+
+  if(getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (char *)&curval, &curlen) == 0)
+    if(curval > val)
+      return;
+
+  setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (const char *)&val, sizeof(val));
+}
 #endif
 
-/* singleipconnect() connects to the given IP only, and it may return without
-   having connected if used from the multi interface. */
-static curl_socket_t
+/*
+ * singleipconnect()
+ *
+ * Note that even on connect fail it returns CURLE_OK, but with 'sock' set to
+ * CURL_SOCKET_BAD. Other errors will however return proper errors.
+ *
+ * singleipconnect() connects to the given IP only, and it may return without
+ * having connected.
+ */
+static CURLcode
 singleipconnect(struct connectdata *conn,
                 const Curl_addrinfo *ai,
-                long timeout_ms,
-                bool *connected)
+                curl_socket_t *sockp)
 {
-  char addr_buf[128];
+  struct Curl_sockaddr_ex addr;
   int rc;
-  int error;
-  bool isconnected;
+  int error = 0;
+  bool isconnected = FALSE;
   struct SessionHandle *data = conn->data;
   curl_socket_t sockfd;
-  CURLcode res;
+  CURLcode res = CURLE_OK;
+  char ipaddress[MAX_IPADR_LEN];
+  long port;
 
-  sockfd = socket(ai->ai_family, conn->socktype, ai->ai_protocol);
-  if (sockfd == CURL_SOCKET_BAD)
-    return CURL_SOCKET_BAD;
+  *sockp = CURL_SOCKET_BAD;
 
-  *connected = FALSE; /* default is not connected */
+  res = Curl_socket(conn, ai, &addr, &sockfd);
+  if(res)
+    /* Failed to create the socket, but still return OK since we signal the
+       lack of socket as well. This allows the parent function to keep looping
+       over alternative addresses/socket families etc. */
+    return CURLE_OK;
 
-  Curl_printable_address(ai, addr_buf, sizeof(addr_buf));
-  infof(data, "  Trying %s... ", addr_buf);
+  /* store remote address and port used in this connection attempt */
+  if(!getaddressinfo((struct sockaddr*)&addr.sa_addr,
+                     ipaddress, &port)) {
+    /* malformed address or bug in inet_ntop, try next address */
+    error = ERRNO;
+    failf(data, "sa_addr inet_ntop() failed with errno %d: %s",
+          error, Curl_strerror(conn, error));
+    Curl_closesocket(conn, sockfd);
+    return CURLE_OK;
+  }
+  infof(data, "  Trying %s...\n", ipaddress);
 
   if(data->set.tcp_nodelay)
     tcpnodelay(conn, sockfd);
 
   nosigpipe(conn, sockfd);
 
+  Curl_sndbufset(sockfd);
+
+  if(data->set.tcp_keepalive)
+    tcpkeepalive(data, sockfd);
+
   if(data->set.fsockopt) {
     /* activate callback for setting socket options */
     error = data->set.fsockopt(data->set.sockopt_client,
                                sockfd,
                                CURLSOCKTYPE_IPCXN);
-    if (error) {
-      sclose(sockfd); /* close the socket and bail out */
-      return CURL_SOCKET_BAD;
+
+    if(error == CURL_SOCKOPT_ALREADY_CONNECTED)
+      isconnected = TRUE;
+    else if(error) {
+      Curl_closesocket(conn, sockfd); /* close the socket and bail out */
+      return CURLE_ABORTED_BY_CALLBACK;
     }
   }
 
   /* possibly bind the local end to an IP, interface or port */
-  res = bindlocal(conn, sockfd);
+  res = bindlocal(conn, sockfd, addr.family);
   if(res) {
-    sclose(sockfd); /* close socket and bail out */
-    return CURL_SOCKET_BAD;
+    Curl_closesocket(conn, sockfd); /* close socket and bail out */
+    if(res == CURLE_UNSUPPORTED_PROTOCOL) {
+      /* The address family is not supported on this interface.
+         We can continue trying addresses */
+      return CURLE_OK;
+    }
+    return res;
   }
 
   /* set socket non-blocking */
-  Curl_nonblock(sockfd, TRUE);
+  curlx_nonblock(sockfd, TRUE);
+
+  conn->connecttime = Curl_tvnow();
+  if(conn->num_addr > 1)
+    Curl_expire_latest(data, conn->timeoutms_per_addr);
 
   /* Connect TCP sockets, bind UDP */
-  if(conn->socktype == SOCK_STREAM)
-    rc = connect(sockfd, ai->ai_addr, ai->ai_addrlen);
-  else
-    rc = 0;
+  if(!isconnected && (conn->socktype == SOCK_STREAM)) {
+    rc = connect(sockfd, &addr.sa_addr, addr.addrlen);
+    if(-1 == rc)
+      error = SOCKERRNO;
+  }
+  else {
+    *sockp = sockfd;
+    return CURLE_OK;
+  }
 
-  if(-1 == rc) {
-    error = Curl_sockerrno();
+#ifdef ENABLE_IPV6
+  conn->bits.ipv6 = (addr.family == AF_INET6)?TRUE:FALSE;
+#endif
 
-    switch (error) {
+  if(-1 == rc) {
+    switch(error) {
     case EINPROGRESS:
     case EWOULDBLOCK:
-#if defined(EAGAIN) && EAGAIN != EWOULDBLOCK
+#if defined(EAGAIN)
+#if (EAGAIN) != (EWOULDBLOCK)
       /* On some platforms EAGAIN and EWOULDBLOCK are the
        * same value, and on others they are different, hence
        * the odd #if
        */
     case EAGAIN:
 #endif
-      rc = waitconnect(sockfd, timeout_ms);
+#endif
+      res = CURLE_OK;
       break;
+
     default:
       /* unknown error, fallthrough and try another address! */
-      failf(data, "Failed to connect to %s: %s",
-            addr_buf, Curl_strerror(conn,error));
+      infof(data, "Immediate connect fail for %s: %s\n",
+            ipaddress, Curl_strerror(conn,error));
       data->state.os_errno = error;
-      break;
-    }
-  }
-
-  /* The 'WAITCONN_TIMEOUT == rc' comes from the waitconnect(), and not from
-     connect(). We can be sure of this since connect() cannot return 1. */
-  if((WAITCONN_TIMEOUT == rc) &&
-     (data->state.used_interface == Curl_if_multi)) {
-    /* Timeout when running the multi interface */
-    return sockfd;
-  }
 
-  isconnected = verifyconnect(sockfd, &error);
-
-  if(!rc && isconnected) {
-    /* we are connected, awesome! */
-    *connected = TRUE; /* this is a true connect */
-    infof(data, "connected\n");
-    return sockfd;
-  }
-  else if(WAITCONN_TIMEOUT == rc)
-    infof(data, "Timeout\n");
-  else {
-    data->state.os_errno = error;
-    infof(data, "%s\n", Curl_strerror(conn, error));
+      /* connect failed */
+      Curl_closesocket(conn, sockfd);
+      res = CURLE_COULDNT_CONNECT;
+    }
   }
 
-  /* connect failed or timed out */
-  sclose(sockfd);
+  if(!res)
+    *sockp = sockfd;
 
-  return CURL_SOCKET_BAD;
+  return res;
 }
 
 /*
@@ -790,116 +1112,229 @@ singleipconnect(struct connectdata *conn,
  */
 
 CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
-                          const struct Curl_dns_entry *remotehost, /* use this one */
-                          curl_socket_t *sockconn,   /* the connected socket */
-                          Curl_addrinfo **addr,      /* the one we used */
-                          bool *connected)           /* really connected? */
+                          const struct Curl_dns_entry *remotehost)
 {
   struct SessionHandle *data = conn->data;
-  curl_socket_t sockfd = CURL_SOCKET_BAD;
-  int aliasindex;
-  int num_addr;
-  Curl_addrinfo *ai;
-  Curl_addrinfo *curr_addr;
-
-  struct timeval after;
   struct timeval before = Curl_tvnow();
+  CURLcode res = CURLE_COULDNT_CONNECT;
 
-  /*************************************************************
-   * Figure out what maximum time we have left
-   *************************************************************/
-  long timeout_ms= DEFAULT_CONNECT_TIMEOUT;
-  long timeout_per_addr;
+  long timeout_ms = Curl_timeleft(data, &before, TRUE);
 
-  *connected = FALSE; /* default to not connected */
+  if(timeout_ms < 0) {
+    /* a precaution, no need to continue if time already is up */
+    failf(data, "Connection time-out");
+    return CURLE_OPERATION_TIMEDOUT;
+  }
 
-  if(data->set.timeout || data->set.connecttimeout) {
-    long has_passed;
+  conn->num_addr = Curl_num_addresses(remotehost->addr);
+  conn->tempaddr[0] = remotehost->addr;
+  conn->tempaddr[1] = NULL;
+  conn->tempsock[0] = CURL_SOCKET_BAD;
+  conn->tempsock[1] = CURL_SOCKET_BAD;
+  Curl_expire(conn->data, HAPPY_EYEBALLS_TIMEOUT);
+
+  /* Max time for the next connection attempt */
+  conn->timeoutms_per_addr =
+    conn->tempaddr[0]->ai_next == NULL ? timeout_ms : timeout_ms / 2;
+
+  /* start connecting to first IP */
+  while(conn->tempaddr[0]) {
+    res = singleipconnect(conn, conn->tempaddr[0], &(conn->tempsock[0]));
+    if(res == CURLE_OK)
+        break;
+    conn->tempaddr[0] = conn->tempaddr[0]->ai_next;
+  }
 
-    /* Evaluate in milliseconds how much time that has passed */
-    has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle);
+  if(conn->tempsock[0] == CURL_SOCKET_BAD)
+    return res;
 
-#ifndef min
-#define min(a, b)   ((a) < (b) ? (a) : (b))
-#endif
+  data->info.numconnects++; /* to track the number of connections made */
 
-    /* get the most strict timeout of the ones converted to milliseconds */
-    if(data->set.timeout && data->set.connecttimeout) {
-      if (data->set.timeout < data->set.connecttimeout)
-        timeout_ms = data->set.timeout*1000;
-      else
-        timeout_ms = data->set.connecttimeout*1000;
-    }
-    else if(data->set.timeout)
-      timeout_ms = data->set.timeout*1000;
-    else
-      timeout_ms = data->set.connecttimeout*1000;
+  return CURLE_OK;
+}
 
-    /* subtract the passed time */
-    timeout_ms -= has_passed;
+struct connfind {
+  struct connectdata *tofind;
+  bool found;
+};
 
-    if(timeout_ms < 0) {
-      /* a precaution, no need to continue if time already is up */
-      failf(data, "Connection time-out");
-      return CURLE_OPERATION_TIMEOUTED;
-    }
+static int conn_is_conn(struct connectdata *conn, void *param)
+{
+  struct connfind *f = (struct connfind *)param;
+  if(conn == f->tofind) {
+    f->found = TRUE;
+    return 1;
   }
-  Curl_expire(data, timeout_ms);
-
-  /* Max time for each address */
-  num_addr = Curl_num_addresses(remotehost->addr);
-  timeout_per_addr = timeout_ms / num_addr;
-
-  ai = remotehost->addr;
+  return 0;
+}
 
-  /* Below is the loop that attempts to connect to all IP-addresses we
-   * know for the given host. One by one until one IP succeeds.
-   */
+/*
+ * Used to extract socket and connectdata struct for the most recent
+ * transfer on the given SessionHandle.
+ *
+ * The returned socket will be CURL_SOCKET_BAD in case of failure!
+ */
+curl_socket_t Curl_getconnectinfo(struct SessionHandle *data,
+                                  struct connectdata **connp)
+{
+  curl_socket_t sockfd;
 
-  if(data->state.used_interface == Curl_if_multi)
-    /* don't hang when doing multi */
-    timeout_per_addr = 0;
+  DEBUGASSERT(data);
 
-  /*
-   * Connecting with a Curl_addrinfo chain
-   */
-  for (curr_addr = ai, aliasindex=0; curr_addr;
-       curr_addr = curr_addr->ai_next, aliasindex++) {
+  /* this only works for an easy handle that has been used for
+     curl_easy_perform()! */
+  if(data->state.lastconnect && data->multi_easy) {
+    struct connectdata *c = data->state.lastconnect;
+    struct connfind find;
+    find.tofind = data->state.lastconnect;
+    find.found = FALSE;
 
-    /* start connecting to the IP curr_addr points to */
-    sockfd = singleipconnect(conn, curr_addr, timeout_per_addr, connected);
+    Curl_conncache_foreach(data->multi_easy->conn_cache, &find, conn_is_conn);
 
-    if(sockfd != CURL_SOCKET_BAD)
-      break;
+    if(!find.found) {
+      data->state.lastconnect = NULL;
+      return CURL_SOCKET_BAD;
+    }
 
-    /* get a new timeout for next attempt */
-    after = Curl_tvnow();
-    timeout_ms -= Curl_tvdiff(after, before);
-    if(timeout_ms < 0) {
-      failf(data, "connect() timed out!");
-      return CURLE_OPERATION_TIMEOUTED;
+    if(connp)
+      /* only store this if the caller cares for it */
+      *connp = c;
+    sockfd = c->sock[FIRSTSOCKET];
+    /* we have a socket connected, let's determine if the server shut down */
+    /* determine if ssl */
+    if(c->ssl[FIRSTSOCKET].use) {
+      /* use the SSL context */
+      if(!Curl_ssl_check_cxn(c))
+        return CURL_SOCKET_BAD;   /* FIN received */
+    }
+/* Minix 3.1 doesn't support any flags on recv; just assume socket is OK */
+#ifdef MSG_PEEK
+    else {
+      /* use the socket */
+      char buf;
+      if(recv((RECV_TYPE_ARG1)c->sock[FIRSTSOCKET], (RECV_TYPE_ARG2)&buf,
+              (RECV_TYPE_ARG3)1, (RECV_TYPE_ARG4)MSG_PEEK) == 0) {
+        return CURL_SOCKET_BAD;   /* FIN received */
+      }
     }
-    before = after;
-  }  /* end of connect-to-each-address loop */
+#endif
+  }
+  else
+    return CURL_SOCKET_BAD;
 
-  if (sockfd == CURL_SOCKET_BAD) {
-    /* no good connect was made */
-    *sockconn = CURL_SOCKET_BAD;
-    failf(data, "couldn't connect to host");
-    return CURLE_COULDNT_CONNECT;
+  return sockfd;
+}
+
+/*
+ * Close a socket.
+ *
+ * 'conn' can be NULL, beware!
+ */
+int Curl_closesocket(struct connectdata *conn,
+                      curl_socket_t sock)
+{
+  if(conn && conn->fclosesocket) {
+    if((sock == conn->sock[SECONDARYSOCKET]) &&
+       conn->sock_accepted[SECONDARYSOCKET])
+      /* if this socket matches the second socket, and that was created with
+         accept, then we MUST NOT call the callback but clear the accepted
+         status */
+      conn->sock_accepted[SECONDARYSOCKET] = FALSE;
+    else
+      return conn->fclosesocket(conn->closesocket_client, sock);
   }
+  sclose(sock);
+
+  if(conn)
+    /* tell the multi-socket code about this */
+    Curl_multi_closed(conn, sock);
+
+  return 0;
+}
+
+/*
+ * Create a socket based on info from 'conn' and 'ai'.
+ *
+ * 'addr' should be a pointer to the correct struct to get data back, or NULL.
+ * 'sockfd' must be a pointer to a socket descriptor.
+ *
+ * If the open socket callback is set, used that!
+ *
+ */
+CURLcode Curl_socket(struct connectdata *conn,
+                     const Curl_addrinfo *ai,
+                     struct Curl_sockaddr_ex *addr,
+                     curl_socket_t *sockfd)
+{
+  struct SessionHandle *data = conn->data;
+  struct Curl_sockaddr_ex dummy;
 
-  /* leave the socket in non-blocking mode */
+  if(!addr)
+    /* if the caller doesn't want info back, use a local temp copy */
+    addr = &dummy;
 
-  /* store the address we use */
-  if(addr)
-    *addr = curr_addr;
+  /*
+   * The Curl_sockaddr_ex structure is basically libcurl's external API
+   * curl_sockaddr structure with enough space available to directly hold
+   * any protocol-specific address structures. The variable declared here
+   * will be used to pass / receive data to/from the fopensocket callback
+   * if this has been set, before that, it is initialized from parameters.
+   */
 
-  /* allow NULL-pointers to get passed in */
-  if(sockconn)
-    *sockconn = sockfd;    /* the socket descriptor we've connected */
+  addr->family = ai->ai_family;
+  addr->socktype = conn->socktype;
+  addr->protocol = conn->socktype==SOCK_DGRAM?IPPROTO_UDP:ai->ai_protocol;
+  addr->addrlen = ai->ai_addrlen;
+
+  if(addr->addrlen > sizeof(struct Curl_sockaddr_storage))
+     addr->addrlen = sizeof(struct Curl_sockaddr_storage);
+  memcpy(&addr->sa_addr, ai->ai_addr, addr->addrlen);
+
+  if(data->set.fopensocket)
+   /*
+    * If the opensocket callback is set, all the destination address
+    * information is passed to the callback. Depending on this information the
+    * callback may opt to abort the connection, this is indicated returning
+    * CURL_SOCKET_BAD; otherwise it will return a not-connected socket. When
+    * the callback returns a valid socket the destination address information
+    * might have been changed and this 'new' address will actually be used
+    * here to connect.
+    */
+    *sockfd = data->set.fopensocket(data->set.opensocket_client,
+                                    CURLSOCKTYPE_IPCXN,
+                                    (struct curl_sockaddr *)addr);
+  else
+    /* opensocket callback not set, so simply create the socket now */
+    *sockfd = socket(addr->family, addr->socktype, addr->protocol);
 
-  data->info.numconnects++; /* to track the number of connections made */
+  if(*sockfd == CURL_SOCKET_BAD)
+    /* no socket, no connection */
+    return CURLE_COULDNT_CONNECT;
+
+#if defined(ENABLE_IPV6) && defined(HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID)
+  if(conn->scope && (addr->family == AF_INET6)) {
+    struct sockaddr_in6 * const sa6 = (void *)&addr->sa_addr;
+    sa6->sin6_scope_id = conn->scope;
+  }
+#endif
 
   return CURLE_OK;
+
+}
+
+#ifdef CURLDEBUG
+/*
+ * Curl_conncontrol() is used to set the conn->bits.close bit on or off. It
+ * MUST be called with the connclose() or connclose() macros with a stated
+ * reason. The reason is only shown in debug builds but helps to figure out
+ * decision paths when connections are or aren't re-used as expected.
+ */
+void Curl_conncontrol(struct connectdata *conn, bool closeit,
+                      const char *reason)
+{
+  infof(conn->data, "Marked for [%s]: %s\n", closeit?"closure":"keep alive",
+        reason);
+  conn->bits.close = closeit; /* the only place in the source code that should
+                                 assign this bit */
 }
+#endif