@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2006, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -24,13 +24,10 @@
 #include "setup.h"
 
 #include <string.h>
-#include <errno.h>
 
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
@@ -57,21 +54,15 @@
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
@@ -88,7 +79,7 @@
 #include "inet_ntoa_r.h"
 #endif
 
-#include "curl_memory.h"
+#include "memory.h"
 /* The last #include file should be: */
 #include "memdebug.h"
 
@@ -105,8 +96,7 @@
  * defined.
  *
  * CURLRES_ARES - is defined if libcurl is built to use c-ares for
- * asynchronous name resolves. It cannot have ENABLE_IPV6 defined at the same
- * time, as c-ares has no ipv6 support. This can be Windows or *nix.
+ * asynchronous name resolves. This can be Windows or *nix.
  *
  * CURLRES_THREADED - is defined if libcurl is built to run under (native)
  * Windows, and then the name resolve will be done in a new thread, and the
@@ -131,7 +121,7 @@
  */
 
 /* These two symbols are for the global DNS cache */
-static curl_hash hostname_cache;
+static struct curl_hash hostname_cache;
 static int host_cache_initialized;
 
 static void freednsentry(void *freethis);
@@ -152,7 +142,7 @@ void Curl_global_host_cache_init(void)
 /*
  * Return a pointer to the global cache
  */
-curl_hash *Curl_global_host_cache_get(void)
+struct curl_hash *Curl_global_host_cache_get(void)
 {
   return &hostname_cache;
 }
@@ -174,20 +164,11 @@ void Curl_global_host_cache_dtor(void)
 int Curl_num_addresses(const Curl_addrinfo *addr)
 {
   int i;
-  for (i = 0; addr; addr = addr->ai_next, i++);
+  for (i = 0; addr; addr = addr->ai_next, i++)
+    ;  /* empty loop */
   return i;
 }
 
-#define GET_SIN_ADDR_FROM_CURL_ADDRINFO(ai_addr, si, sin, sinaddr, ip) \
-  { \
-  union { \
-    struct si* vsi; \
-    struct sin* vsin;\
-  } vi; \
-  vi.vsi = ai_addr; \
-  ip = &(vi.vsin->sinaddr); \
-  }
-
 /*
  * Curl_printable_address() returns a printable version of the 1st address
  * given in the 'ip' argument. The result will be stored in the buf that is
@@ -198,17 +179,13 @@ int Curl_num_addresses(const Curl_addrinfo *addr)
 const char *Curl_printable_address(const Curl_addrinfo *ip,
                                    char *buf, size_t bufsize)
 {
+  const void *ip4 = &((const struct sockaddr_in*)ip->ai_addr)->sin_addr;
   int af = ip->ai_family;
-  const void *ip4;
 #ifdef CURLRES_IPV6
-  const void *ip6;
-  GET_SIN_ADDR_FROM_CURL_ADDRINFO(ip->ai_addr, sockaddr, sockaddr_in6,
-    sin6_addr, ip6);
+  const void *ip6 = &((const struct sockaddr_in6*)ip->ai_addr)->sin6_addr;
 #else
   const void *ip6 = NULL;
 #endif
-  GET_SIN_ADDR_FROM_CURL_ADDRINFO(ip->ai_addr, sockaddr, sockaddr_in,
-    sin_addr, ip4);
 
   return Curl_inet_ntop(af, af == AF_INET ? ip4 : ip6, buf, bufsize);
 }
@@ -218,7 +195,7 @@ const char *Curl_printable_address(const Curl_addrinfo *ip,
  * the DNS caching.
  */
 static char *
-create_hostcache_id(char *server, int port)
+create_hostcache_id(const char *server, int port)
 {
   /* create and return the new allocated entry */
   return aprintf("%s:%d", server, port);
@@ -257,7 +234,7 @@ hostcache_timestamp_remove(void *datap, void *hc)
  * Prune the DNS cache. This assumes that a lock has already been taken.
  */
 static void
-hostcache_prune(curl_hash *hostcache, int cache_timeout, time_t now)
+hostcache_prune(struct curl_hash *hostcache, int cache_timeout, time_t now)
 {
   struct hostcache_prune_data user;
 
@@ -277,8 +254,9 @@ void Curl_hostcache_prune(struct SessionHandle *data)
 {
   time_t now;
 
-  if(data->set.dns_cache_timeout == -1)
-    /* cache forever means never prune! */
+  if((data->set.dns_cache_timeout == -1) || !data->dns.hostcache)
+    /* cache forever means never prune, and NULL hostcache means
+       we can't do it */
     return;
 
   if(data->share)
@@ -287,14 +265,47 @@ void Curl_hostcache_prune(struct SessionHandle *data)
   time(&now);
 
   /* Remove outdated and unused entries from the hostcache */
-  hostcache_prune(data->hostcache,
+  hostcache_prune(data->dns.hostcache,
                   data->set.dns_cache_timeout,
                   now);
 
   if(data->share)
     Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
 }
 
+static int
+remove_entry_if_stale(struct SessionHandle *data, struct Curl_dns_entry *dns)
+{
+  struct hostcache_prune_data user;
+
+  if( !dns || (data->set.dns_cache_timeout == -1) || !data->dns.hostcache)
+    /* cache forever means never prune, and NULL hostcache means
+       we can't do it */
+    return 0;
+
+  time(&user.now);
+  user.cache_timeout = data->set.dns_cache_timeout;
+
+  if ( !hostcache_timestamp_remove(&user,dns) )
+    return 0;
+
+  /* ok, we do need to clear the cache. although we need to remove just a
+     single entry we clean the entire hash, as no explicit delete function
+     is provided */
+  if(data->share)
+    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);
+
+  Curl_hash_clean_with_criterium(data->dns.hostcache,
+                                 (void *) &user,
+                                 hostcache_timestamp_remove);
+
+  if(data->share)
+    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
+
+  return 1;
+}
+
+
 #ifdef HAVE_SIGSETJMP
 /* Beware this is a global and unique instance. This is used to store the
    return address that we can jump back to from inside a signal handler. This
@@ -315,7 +326,7 @@ sigjmp_buf curl_jmpenv;
 struct Curl_dns_entry *
 Curl_cache_addr(struct SessionHandle *data,
                 Curl_addrinfo *addr,
-                char *hostname,
+                const char *hostname,
                 int port)
 {
   char *entry_id;
@@ -332,7 +343,7 @@ Curl_cache_addr(struct SessionHandle *data,
   entry_len = strlen(entry_id);
 
   /* Create a new cache entry */
-  dns = (struct Curl_dns_entry *) malloc(sizeof(struct Curl_dns_entry));
+  dns = (struct Curl_dns_entry *) calloc(sizeof(struct Curl_dns_entry), 1);
   if (!dns) {
     free(entry_id);
     return NULL;
@@ -344,7 +355,8 @@ Curl_cache_addr(struct SessionHandle *data,
   /* Store the resolved data in our DNS cache. This function may return a
      pointer to an existing struct already present in the hash, and it may
      return the same argument we pass in. Make no assumptions. */
-  dns2 = Curl_hash_add(data->hostcache, entry_id, entry_len+1, (void *)dns);
+  dns2 = Curl_hash_add(data->dns.hostcache, entry_id, entry_len+1,
+                       (void *)dns);
   if(!dns2) {
     /* Major badness, run away. */
     free(dns);
@@ -381,31 +393,30 @@ Curl_cache_addr(struct SessionHandle *data,
  */
 
 int Curl_resolv(struct connectdata *conn,
-                char *hostname,
+                const char *hostname,
                 int port,
                 struct Curl_dns_entry **entry)
 {
-  char *entry_id;
+  char *entry_id = NULL;
   struct Curl_dns_entry *dns = NULL;
   size_t entry_len;
   int wait;
   struct SessionHandle *data = conn->data;
   CURLcode result;
-
-  /* default to failure */
   int rc;
   *entry = NULL;
 
 #ifdef HAVE_SIGSETJMP
   /* this allows us to time-out from the name resolver, as the timeout
      will generate a signal and we will siglongjmp() from that here */
-  if(!data->set.no_signal && sigsetjmp(curl_jmpenv, 1)) {
-    /* this is coming from a siglongjmp() */
-    failf(data, "name lookup timed out");
-    return CURLRESOLV_ERROR;
+  if(!data->set.no_signal) {
+    if (sigsetjmp(curl_jmpenv, 1)) {
+      /* this is coming from a siglongjmp() */
+      failf(data, "name lookup timed out");
+      return CURLRESOLV_ERROR;
+    }
   }
 #endif
-  rc = CURLRESOLV_ERROR;
 
   /* Create an entry id, based upon the hostname and port */
   entry_id = create_hostcache_id(hostname, port);
@@ -419,14 +430,21 @@ int Curl_resolv(struct connectdata *conn,
     Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);
 
   /* See if its already in our dns cache */
-  dns = Curl_hash_pick(data->hostcache, entry_id, entry_len+1);
+  dns = Curl_hash_pick(data->dns.hostcache, entry_id, entry_len+1);
 
   if(data->share)
     Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
 
   /* free the allocated entry_id again */
   free(entry_id);
 
+  /* See whether the returned entry is stale. Deliberately done after the
+     locked block */
+  if ( remove_entry_if_stale(data,dns) )
+    dns = NULL; /* the memory deallocation is being handled by the hash */
+
+  rc = CURLRESOLV_ERROR; /* default to failure */
+
   if (!dns) {
     /* The entry was not in the cache. Resolve it to IP address */
 
@@ -474,7 +492,11 @@ int Curl_resolv(struct connectdata *conn,
     }
   }
   else {
+    if(data->share)
+      Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);
     dns->inuse++; /* we use it! */
+    if(data->share)
+      Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
     rc = CURLRESOLV_RESOLVED;
   }
 
@@ -516,7 +538,7 @@ static void freednsentry(void *freethis)
 /*
  * Curl_mk_dnscache() creates a new DNS cache and returns the handle for it.
  */
-curl_hash *Curl_mk_dnscache(void)
+struct curl_hash *Curl_mk_dnscache(void)
 {
   return Curl_hash_alloc(7, freednsentry);
 }
@@ -531,10 +553,84 @@ curl_hash *Curl_mk_dnscache(void)
  * returns a pointer to the malloc()ed copy. You need to call free() on the
  * returned buffer when you're done with it.
  */
-Curl_addrinfo *Curl_addrinfo_copy(void *org, int port)
+Curl_addrinfo *Curl_addrinfo_copy(const void *org, int port)
 {
-  struct hostent *orig = org;
+  const struct hostent *orig = org;
 
   return Curl_he2ai(orig, port);
 }
 #endif /* CURLRES_ADDRINFO_COPY */
+
+/***********************************************************************
+ * Only for plain-ipv4 and c-ares builds
+ **********************************************************************/
+
+#if defined(CURLRES_IPV4) || defined(CURLRES_ARES)
+/*
+ * This is a function for freeing name information in a protocol independent
+ * way.
+ */
+void Curl_freeaddrinfo(Curl_addrinfo *ai)
+{
+  Curl_addrinfo *next;
+
+  /* walk over the list and free all entries */
+  while(ai) {
+    next = ai->ai_next;
+    free(ai);
+    ai = next;
+  }
+}
+
+struct namebuf {
+  struct hostent hostentry;
+  char *h_addr_list[2];
+  struct in_addr addrentry;
+  char h_name[16]; /* 123.123.123.123 = 15 letters is maximum */
+};
+
+/*
+ * Curl_ip2addr() takes a 32bit ipv4 internet address as input parameter
+ * together with a pointer to the string version of the address, and it
+ * returns a Curl_addrinfo chain filled in correctly with information for this
+ * address/host.
+ *
+ * The input parameters ARE NOT checked for validity but they are expected
+ * to have been checked already when this is called.
+ */
+Curl_addrinfo *Curl_ip2addr(in_addr_t num, const char *hostname, int port)
+{
+  Curl_addrinfo *ai;
+  struct hostent *h;
+  struct in_addr *addrentry;
+  struct namebuf buffer;
+  struct namebuf *buf = &buffer;
+
+  h = &buf->hostentry;
+  h->h_addr_list = &buf->h_addr_list[0];
+  addrentry = &buf->addrentry;
+#ifdef _CRAYC
+  /* On UNICOS, s_addr is a bit field and for some reason assigning to it
+   * doesn't work.  There must be a better fix than this ugly hack.
+   */
+  memcpy(addrentry, &num, SIZEOF_in_addr);
+#else
+  addrentry->s_addr = num;
+#endif
+  h->h_addr_list[0] = (char*)addrentry;
+  h->h_addr_list[1] = NULL;
+  h->h_addrtype = AF_INET;
+  h->h_length = sizeof(*addrentry);
+  h->h_name = &buf->h_name[0];
+  h->h_aliases = NULL;
+
+  /* Now store the dotted version of the address */
+  snprintf((char *)h->h_name, 16, "%s", hostname);
+
+  ai = Curl_he2ai(h, port);
+
+  return ai;
+}
+#endif
+
+