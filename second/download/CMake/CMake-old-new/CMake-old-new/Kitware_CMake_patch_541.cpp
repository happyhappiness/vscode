@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2006, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -26,11 +26,9 @@
 #include <string.h>
 #include <errno.h>
 
-#define _REENTRANT
-
-#if defined(WIN32) && !defined(__GNUC__) || defined(__MINGW32__)
+#ifdef NEED_MALLOC_H
 #include <malloc.h>
-#else
+#endif
 #ifdef HAVE_SYS_TYPES_H
 #include <sys/types.h>
 #endif
@@ -57,28 +55,23 @@
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
 
 #define _MPRINTF_REPLACE /* use our functions only */
 #include <curl/mprintf.h>
@@ -87,31 +80,14 @@
 #include "inet_ntoa_r.h"
 #endif
 
-#include "curl_memory.h"
+#include "memory.h"
 /* The last #include file should be: */
 #include "memdebug.h"
 
 /***********************************************************************
  * Only for plain-ipv4 builds
  **********************************************************************/
 #ifdef CURLRES_IPV4 /* plain ipv4 code coming up */
-
-/*
- * This is a function for freeing name information in a protocol independent
- * way.
- */
-void Curl_freeaddrinfo(Curl_addrinfo *ai)
-{
-  Curl_addrinfo *next;
-
-  /* walk over the list and free all entries */
-  while(ai) {
-    next = ai->ai_next;
-    free(ai);
-    ai = next;
-  }
-}
-
 /*
  * Curl_ipvalid() checks what CURL_IPRESOLVE_* requirements that might've
  * been set and returns TRUE if they are OK.
@@ -125,57 +101,13 @@ bool Curl_ipvalid(struct SessionHandle *data)
   return TRUE; /* OK, proceed */
 }
 
-struct namebuf {
-  struct hostent hostentry;
-  char *h_addr_list[2];
-  struct in_addr addrentry;
-  char h_name[16]; /* 123.123.123.123 = 15 letters is maximum */
-};
-
-/*
- * Curl_ip2addr() takes a 32bit ipv4 internet address as input parameter
- * together with a pointer to the string version of the address, and it
- * returns a Curl_addrinfo chain filled in correctly with information for this
- * address/host.
- *
- * The input parameters ARE NOT checked for validity but they are expected
- * to have been checked already when this is called.
- */
-Curl_addrinfo *Curl_ip2addr(in_addr_t num, char *hostname, int port)
-{
-  Curl_addrinfo *ai;
-  struct hostent *h;
-  struct in_addr *addrentry;
-  struct namebuf buffer;
-  struct namebuf *buf = &buffer;
-
-  h = &buf->hostentry;
-  h->h_addr_list = &buf->h_addr_list[0];
-  addrentry = &buf->addrentry;
-  addrentry->s_addr = num;
-  h->h_addr_list[0] = (char*)addrentry;
-  h->h_addr_list[1] = NULL;
-  h->h_addrtype = AF_INET;
-  h->h_length = sizeof(*addrentry);
-  h->h_name = &buf->h_name[0];
-  h->h_aliases = NULL;
-
-  /* Now store the dotted version of the address */
-  snprintf((char*)(h->h_name), 16, "%s", hostname);
-
-  ai = Curl_he2ai(h, port);
-
-  return ai;
-}
-
 #ifdef CURLRES_SYNCH /* the functions below are for synchronous resolves */
 
 /*
  * Curl_getaddrinfo() - the ipv4 synchronous version.
  *
- * The original code to this function was once stolen from the Dancer source
- * code, written by Bjorn Reese, it has since been patched and modified
- * considerably.
+ * The original code to this function was from the Dancer source code, written
+ * by Bjorn Reese, it has since been patched and modified considerably.
  *
  * gethostbyname_r() is the thread-safe version of the gethostbyname()
  * function. When we build for plain IPv4, we attempt to use this
@@ -188,7 +120,7 @@ Curl_addrinfo *Curl_ip2addr(in_addr_t num, char *hostname, int port)
  *
  */
 Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
-                                char *hostname,
+                                const char *hostname,
                                 int port,
                                 int *waitp)
 {
@@ -202,11 +134,9 @@ Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
 
   *waitp = 0; /* don't wait, we act synchronously */
 
-  in=inet_addr(hostname);
-  if (in != CURL_INADDR_NONE) {
+  if(1 == Curl_inet_pton(AF_INET, hostname, &in))
     /* This is a dotted IP address 123.123.123.123-style */
     return Curl_ip2addr(in, hostname, port);
-  }
 
 #if defined(HAVE_GETHOSTBYNAME_R)
   /*
@@ -370,55 +300,55 @@ Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
 }
 
 #endif /* CURLRES_SYNCH */
+#endif /* CURLRES_IPV4 */
 
 /*
  * Curl_he2ai() translates from a hostent struct to a Curl_addrinfo struct.
  * The Curl_addrinfo is meant to work like the addrinfo struct does for IPv6
  * stacks, but for all hosts and environments.
+ *
+ *   Curl_addrinfo defined in "lib/hostip.h"
+ *
+ *     struct Curl_addrinfo {
+ *       int                   ai_flags;
+ *       int                   ai_family;
+ *       int                   ai_socktype;
+ *       int                   ai_protocol;
+ *       socklen_t             ai_addrlen;   * Follow rfc3493 struct addrinfo *
+ *       char                 *ai_canonname;
+ *       struct sockaddr      *ai_addr;
+ *       struct Curl_addrinfo *ai_next;
+ *     };
+ *
+ *   hostent defined in <netdb.h>
+ *
+ *     struct hostent {
+ *       char    *h_name;
+ *       char    **h_aliases;
+ *       int     h_addrtype;
+ *       int     h_length;
+ *       char    **h_addr_list;
+ *     };
+ *
+ *   for backward compatibility:
+ *
+ *     #define h_addr  h_addr_list[0]
+ */
 
-struct Curl_addrinfo {
-  int     ai_flags;
-  int     ai_family;
-  int     ai_socktype;
-  int     ai_protocol;
-  size_t  ai_addrlen;
-  struct sockaddr *ai_addr;
-  char   *ai_canonname;
-  struct addrinfo *ai_next;
-};
-
-struct hostent {
-  char    *h_name;        * official name of host *
-  char    **h_aliases;    * alias list *
-  int     h_addrtype;     * host address type *
-  int     h_length;       * length of address *
-  char    **h_addr_list;  * list of addresses *
-}
-#define h_addr  h_addr_list[0]  * for backward compatibility *
-
-*/
-
-Curl_addrinfo *Curl_he2ai(struct hostent *he, int port)
+Curl_addrinfo *Curl_he2ai(const struct hostent *he, int port)
 {
   Curl_addrinfo *ai;
   Curl_addrinfo *prevai = NULL;
   Curl_addrinfo *firstai = NULL;
+  struct sockaddr_in *addr;
   int i;
-
-  union {
-    struct in_addr *addr;
-    char* list;
-  } curr;
-  union {
-    struct sockaddr_in* addr_in;
-    struct sockaddr* addr;
-  } address;
+  struct in_addr *curr;
 
   if(!he)
     /* no input == no output! */
     return NULL;
 
-  for(i=0; (curr.list = he->h_addr_list[i]); i++) {
+  for(i=0; (curr = (struct in_addr *)he->h_addr_list[i]) != NULL; i++) {
 
     ai = calloc(1, sizeof(Curl_addrinfo) + sizeof(struct sockaddr_in));
 
@@ -434,23 +364,26 @@ Curl_addrinfo *Curl_he2ai(struct hostent *he, int port)
       prevai->ai_next = ai;
 
     ai->ai_family = AF_INET;              /* we only support this */
-    ai->ai_socktype = SOCK_STREAM;        /* we only support this */
+
+    /* we return all names as STREAM, so when using this address for TFTP
+       the type must be ignored and conn->socktype be used instead! */
+    ai->ai_socktype = SOCK_STREAM;
+
     ai->ai_addrlen = sizeof(struct sockaddr_in);
     /* make the ai_addr point to the address immediately following this struct
        and use that area to store the address */
-    ai->ai_addr = (struct sockaddr *) (ai + 1);
+    ai->ai_addr = (struct sockaddr *) ((char*)ai + sizeof(Curl_addrinfo));
 
     /* leave the rest of the struct filled with zero */
 
-    address.addr = ai->ai_addr; /* storage area for this info */
+    addr = (struct sockaddr_in *)ai->ai_addr; /* storage area for this info */
 
-    memcpy((char *)&(address.addr_in->sin_addr), curr.addr, sizeof(struct in_addr));
-    address.addr_in->sin_family = he->h_addrtype;
-    address.addr_in->sin_port = htons((unsigned short)port);
+    memcpy((char *)&(addr->sin_addr), curr, sizeof(struct in_addr));
+    addr->sin_family = he->h_addrtype;
+    addr->sin_port = htons((unsigned short)port);
 
     prevai = ai;
   }
   return firstai;
 }
 
-#endif /* CURLRES_IPV4 */