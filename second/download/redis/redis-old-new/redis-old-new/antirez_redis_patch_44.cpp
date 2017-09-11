@@ -1,7 +1,9 @@
 /* Extracted from anet.c to work properly with Hiredis error reporting.
  *
- * Copyright (c) 2006-2011, Salvatore Sanfilippo <antirez at gmail dot com>
- * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2009-2011, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010-2014, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2015, Matt Stancliff <matt at genges dot com>,
+ *                     Jan-Erik Rediger <janerik at fnordig dot com>
  *
  * All rights reserved.
  *
@@ -39,9 +41,13 @@
 #define AF_LOCAL AF_UNIX
 #endif
 
-int redisCheckSocketError(redisContext *c, int fd);
-int redisContextSetTimeout(redisContext *c, struct timeval tv);
-int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout);
-int redisContextConnectUnix(redisContext *c, const char *path, struct timeval *timeout);
+int redisCheckSocketError(redisContext *c);
+int redisContextSetTimeout(redisContext *c, const struct timeval tv);
+int redisContextConnectTcp(redisContext *c, const char *addr, int port, const struct timeval *timeout);
+int redisContextConnectBindTcp(redisContext *c, const char *addr, int port,
+                               const struct timeval *timeout,
+                               const char *source_addr);
+int redisContextConnectUnix(redisContext *c, const char *path, const struct timeval *timeout);
+int redisKeepAlive(redisContext *c, int interval);
 
 #endif