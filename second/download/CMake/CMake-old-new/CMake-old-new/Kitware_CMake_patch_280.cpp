@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -53,16 +53,46 @@
 #include "inet_ntop.h"
 #include "strequal.h"
 #include "if2ip.h"
-
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
+#include "curl_printf.h"
 
 #include "curl_memory.h"
 /* The last #include file should be: */
 #include "memdebug.h"
 
 /* ------------------------------------------------------------------ */
 
+/* Return the scope of the given address. */
+unsigned int Curl_ipv6_scope(const struct sockaddr *sa)
+{
+#ifndef ENABLE_IPV6
+  (void) sa;
+#else
+  if(sa->sa_family == AF_INET6) {
+    const struct sockaddr_in6 * sa6 = (const struct sockaddr_in6 *) sa;
+    const unsigned char * b = sa6->sin6_addr.s6_addr;
+    unsigned short w = (unsigned short) ((b[0] << 8) | b[1]);
+
+    switch(w & 0xFFC0) {
+    case 0xFE80:
+      return IPV6_SCOPE_LINKLOCAL;
+    case 0xFEC0:
+      return IPV6_SCOPE_SITELOCAL;
+    case 0x0000:
+      w = b[1] | b[2] | b[3] | b[4] | b[5] | b[6] | b[7] | b[8] | b[9] |
+          b[10] | b[11] | b[12] | b[13] | b[14];
+      if(w || b[15] != 0x01)
+        break;
+      return IPV6_SCOPE_NODELOCAL;
+    default:
+      break;
+    }
+  }
+#endif
+
+  return IPV6_SCOPE_GLOBAL;
+}
+
+
 #if defined(HAVE_GETIFADDRS)
 
 bool Curl_if_is_interface_name(const char *interf)
@@ -84,41 +114,58 @@ bool Curl_if_is_interface_name(const char *interf)
 }
 
 if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
-                          const char *interf, char *buf, int buf_size)
+                          unsigned int remote_scope_id, const char *interf,
+                          char *buf, int buf_size)
 {
   struct ifaddrs *iface, *head;
   if2ip_result_t res = IF2IP_NOT_FOUND;
 
 #ifndef ENABLE_IPV6
   (void) remote_scope;
+
+#ifndef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
+  (void) remote_scope_id;
+#endif
+
 #endif
 
   if(getifaddrs(&head) >= 0) {
-    for(iface=head; iface != NULL; iface=iface->ifa_next) {
+    for(iface = head; iface != NULL; iface=iface->ifa_next) {
       if(iface->ifa_addr != NULL) {
         if(iface->ifa_addr->sa_family == af) {
           if(curl_strequal(iface->ifa_name, interf)) {
             void *addr;
             char *ip;
-            char scope[12]="";
+            char scope[12] = "";
             char ipstr[64];
 #ifdef ENABLE_IPV6
             if(af == AF_INET6) {
               unsigned int scopeid = 0;
+              unsigned int ifscope = Curl_ipv6_scope(iface->ifa_addr);
+
+              if(ifscope != remote_scope) {
+                /* We are interested only in interface addresses whose
+                   scope matches the remote address we want to
+                   connect to: global for global, link-local for
+                   link-local, etc... */
+                if(res == IF2IP_NOT_FOUND) res = IF2IP_AF_NOT_SUPPORTED;
+                continue;
+              }
+
               addr = &((struct sockaddr_in6 *)iface->ifa_addr)->sin6_addr;
 #ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
               /* Include the scope of this interface as part of the address */
               scopeid =
                 ((struct sockaddr_in6 *)iface->ifa_addr)->sin6_scope_id;
-#endif
-              if(scopeid != remote_scope) {
-                /* We are interested only in interface addresses whose
-                   scope ID matches the remote address we want to
-                   connect to: global (0) for global, link-local for
-                   link-local, etc... */
-                if(res == IF2IP_NOT_FOUND) res = IF2IP_AF_NOT_SUPPORTED;
+
+              /* If given, scope id should match. */
+              if(remote_scope_id && scopeid != remote_scope_id) {
+                if(res == IF2IP_NOT_FOUND)
+                  res = IF2IP_AF_NOT_SUPPORTED;
+
                 continue;
               }
+#endif
               if(scopeid)
                 snprintf(scope, sizeof(scope), "%%%u", scopeid);
             }
@@ -137,8 +184,10 @@ if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
         }
       }
     }
+
     freeifaddrs(head);
   }
+
   return res;
 }
 
@@ -149,12 +198,13 @@ bool Curl_if_is_interface_name(const char *interf)
   /* This is here just to support the old interfaces */
   char buf[256];
 
-  return (Curl_if2ip(AF_INET, 0, interf, buf, sizeof(buf)) ==
+  return (Curl_if2ip(AF_INET, 0 /* unused */, 0, interf, buf, sizeof(buf)) ==
           IF2IP_NOT_FOUND) ? FALSE : TRUE;
 }
 
 if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
-                          const char *interf, char *buf, int buf_size)
+                          unsigned int remote_scope_id, const char *interf,
+                          char *buf, int buf_size)
 {
   struct ifreq req;
   struct in_addr in;
@@ -163,6 +213,7 @@ if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
   size_t len;
 
   (void)remote_scope;
+  (void)remote_scope_id;
 
   if(!interf || (af != AF_INET))
     return IF2IP_NOT_FOUND;
@@ -205,10 +256,12 @@ bool Curl_if_is_interface_name(const char *interf)
 }
 
 if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
-                          const char *interf, char *buf, int buf_size)
+                          unsigned int remote_scope_id, const char *interf,
+                          char *buf, int buf_size)
 {
     (void) af;
     (void) remote_scope;
+    (void) remote_scope_id;
     (void) interf;
     (void) buf;
     (void) buf_size;