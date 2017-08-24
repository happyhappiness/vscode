@@ -1,16 +1,16 @@
 /***************************************************************************
- *                                  _   _ ____  _     
- *  Project                     ___| | | |  _ \| |    
- *                             / __| | | | |_) | |    
- *                            | (__| |_| |  _ <| |___ 
+ *                                  _   _ ____  _
+ *  Project                     ___| | | |  _ \| |
+ *                             / __| | | | |_) | |
+ *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2006, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
  * are also available at http://curl.haxx.se/docs/copyright.html.
- * 
+ *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
  * furnished to do so, under the terms of the COPYING file.
@@ -24,13 +24,10 @@
 #include "setup.h"
 
 #include <string.h>
-#include <errno.h>
-
-#define _REENTRANT
 
-#if defined(WIN32) && !defined(__GNUC__) || defined(__MINGW32__)
+#ifdef NEED_MALLOC_H
 #include <malloc.h>
-#else
+#endif
 #ifdef HAVE_SYS_TYPES_H
 #include <sys/types.h>
 #endif
@@ -57,28 +54,24 @@
 #include <inet.h>
 #include <stdlib.h>
 #endif
-#endif
 
 #ifdef HAVE_SETJMP_H
 #include <setjmp.h>
 #endif
 
-#ifdef WIN32
+#ifdef HAVE_PROCESS_H
 #include <process.h>
 #endif
 
-#if (defined(NETWARE) && defined(__NOVELL_LIBC__))
-#undef in_addr_t
-#define in_addr_t unsigned long
-#endif
-
 #include "urldata.h"
 #include "sendf.h"
 #include "hostip.h"
 #include "hash.h"
 #include "share.h"
 #include "strerror.h"
 #include "url.h"
+#include "inet_pton.h"
+#include "connect.h"
 
 #define _MPRINTF_REPLACE /* use our functions only */
 #include <curl/mprintf.h>
@@ -87,14 +80,15 @@
 #include "inet_ntoa_r.h"
 #endif
 
-#include "curl_memory.h"
+#include "memory.h"
 /* The last #include file should be: */
 #include "memdebug.h"
 
 /***********************************************************************
  * Only for ipv6-enabled builds
  **********************************************************************/
 #ifdef CURLRES_IPV6
+#ifndef CURLRES_ARES
 /*
  * This is a wrapper function for freeing name information in a protocol
  * independent way. This takes care of using the appropriate underlaying
@@ -111,19 +105,20 @@ void Curl_freeaddrinfo(Curl_addrinfo *p)
  * address. But this is an ipv6 build and then we don't copy the address, we
  * just return the same pointer!
  */
-Curl_addrinfo *Curl_addrinfo_copy(void *source, int port)
+Curl_addrinfo *Curl_addrinfo_copy(const void *orig, int port)
 {
   (void) port;
-  return source;
+  return (Curl_addrinfo*)orig;
 }
-#endif
+#endif  /* CURLRES_ASYNCH */
+#endif  /* CURLRES_ARES */
 
 #ifdef CURLDEBUG
 /* These are strictly for memory tracing and are using the same style as the
  * family otherwise present in memdebug.c. I put these ones here since they
  * require a bunch of structs I didn't wanna include in memdebug.c
  */
-int curl_dogetaddrinfo(char *hostname, char *service,
+int curl_dogetaddrinfo(const char *hostname, const char *service,
                        struct addrinfo *hints,
                        struct addrinfo **result,
                        int line, const char *source)
@@ -143,12 +138,22 @@ int curl_dogetaddrinfo(char *hostname, char *service,
   return res;
 }
 
-int curl_dogetnameinfo(const struct sockaddr *sa, socklen_t salen,
-                       char *host, size_t hostlen,
-                       char *serv, size_t servlen, int flags,
+/*
+ * For CURLRES_ARS, this should be written using ares_gethostbyaddr()
+ * (ignoring the fact c-ares doesn't return 'serv').
+ */
+#ifdef HAVE_GETNAMEINFO
+int curl_dogetnameinfo(GETNAMEINFO_QUAL_ARG1 GETNAMEINFO_TYPE_ARG1 sa,
+                       GETNAMEINFO_TYPE_ARG2 salen,
+                       char *host, GETNAMEINFO_TYPE_ARG46 hostlen,
+                       char *serv, GETNAMEINFO_TYPE_ARG46 servlen,
+                       GETNAMEINFO_TYPE_ARG7 flags,
                        int line, const char *source)
 {
-  int res=(getnameinfo)(sa, salen, host, hostlen, serv, servlen, flags);
+  int res = (getnameinfo)(sa, salen,
+                          host, hostlen,
+                          serv, servlen,
+                          flags);
   if(0 == res) {
     /* success */
     if(logfile)
@@ -162,6 +167,7 @@ int curl_dogetnameinfo(const struct sockaddr *sa, socklen_t salen,
   }
   return res;
 }
+#endif
 
 void curl_dofreeaddrinfo(struct addrinfo *freethis,
                          int line, const char *source)
@@ -171,8 +177,7 @@ void curl_dofreeaddrinfo(struct addrinfo *freethis,
     fprintf(logfile, "ADDR %s:%d freeaddrinfo(%p)\n",
             source, line, (void *)freethis);
 }
-
-#endif
+#endif  /* CURLDEBUG */
 
 /*
  * Curl_ipvalid() checks what CURL_IPRESOLVE_* requirements that might've
@@ -191,23 +196,46 @@ bool Curl_ipvalid(struct SessionHandle *data)
   return TRUE;
 }
 
-#ifndef USE_THREADING_GETADDRINFO
+#if !defined(USE_THREADING_GETADDRINFO) && !defined(CURLRES_ARES)
+
+#ifdef DEBUG_ADDRINFO
+static void dump_addrinfo(struct connectdata *conn, const struct addrinfo *ai)
+{
+  printf("dump_addrinfo:\n");
+  for ( ; ai; ai = ai->ai_next) {
+    char  buf[INET6_ADDRSTRLEN];
+
+    printf("    fam %2d, CNAME %s, ",
+           ai->ai_family, ai->ai_canonname ? ai->ai_canonname : "<none>");
+    if (Curl_printable_address(ai, buf, sizeof(buf)))
+      printf("%s\n", buf);
+    else
+      printf("failed; %s\n", Curl_strerror(conn, Curl_sockerrno()));
+  }
+}
+#else
+#define dump_addrinfo(x,y)
+#endif
+
 /*
- * Curl_getaddrinfo() when built ipv6-enabled (non-threading version).
+ * Curl_getaddrinfo() when built ipv6-enabled (non-threading and
+ * non-ares version).
  *
  * Returns name information about the given hostname and port number. If
  * successful, the 'addrinfo' is returned and the forth argument will point to
  * memory we need to free after use. That memory *MUST* be freed with
  * Curl_freeaddrinfo(), nothing else.
  */
 Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
-                                char *hostname,
+                                const char *hostname,
                                 int port,
                                 int *waitp)
 {
   struct addrinfo hints, *res;
   int error;
   char sbuf[NI_MAXSERV];
+  char *sbufptr = NULL;
+  char addrbuf[128];
   curl_socket_t s;
   int pf;
   struct SessionHandle *data = conn->data;
@@ -216,7 +244,7 @@ Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
 
   /* see if we have an IPv6 stack */
   s = socket(PF_INET6, SOCK_DGRAM, 0);
-  if (s < 0) {
+  if (s == CURL_SOCKET_BAD) {
     /* Some non-IPv6 stacks have been found to make very slow name resolves
      * when PF_UNSPEC is used, so thus we switch to a mere PF_INET lookup if
      * the stack seems to be a non-ipv6 one. */
@@ -244,20 +272,35 @@ Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
       break;
     }
   }
- 
+
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = pf;
-  hints.ai_socktype = SOCK_STREAM;
-  hints.ai_flags = AI_CANONNAME;
-  snprintf(sbuf, sizeof(sbuf), "%d", port);
-  error = getaddrinfo(hostname, sbuf, &hints, &res);
+  hints.ai_socktype = conn->socktype;
+
+  if((1 == Curl_inet_pton(AF_INET, hostname, addrbuf)) ||
+     (1 == Curl_inet_pton(AF_INET6, hostname, addrbuf))) {
+    /* the given address is numerical only, prevent a reverse lookup */
+    hints.ai_flags = AI_NUMERICHOST;
+  }
+#if 0 /* removed nov 8 2005 before 7.15.1 */
+  else
+    hints.ai_flags = AI_CANONNAME;
+#endif
+
+  if(port) {
+    snprintf(sbuf, sizeof(sbuf), "%d", port);
+    sbufptr=sbuf;
+  }
+  error = getaddrinfo(hostname, sbufptr, &hints, &res);
   if (error) {
-    infof(data, "getaddrinfo(3) failed for %s:%d\n", hostname, port);    
+    infof(data, "getaddrinfo(3) failed for %s:%d\n", hostname, port);
     return NULL;
   }
 
+  dump_addrinfo(conn, res);
+
   return res;
 }
-#endif /* USE_THREADING_GETADDRINFO */
+#endif /* !USE_THREADING_GETADDRINFO && !CURLRES_ARES */
 #endif /* ipv6 */
 