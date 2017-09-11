@@ -1,7 +1,7 @@
 /* Extracted from anet.c to work properly with Hiredis error reporting.
  *
- * Copyright (c) 2006-2010, Salvatore Sanfilippo <antirez at gmail dot com>
- * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2006-2011, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
  *
  * All rights reserved.
  *
@@ -39,6 +39,7 @@
 #define AF_LOCAL AF_UNIX
 #endif
 
+int redisCheckSocketError(redisContext *c, int fd);
 int redisContextSetTimeout(redisContext *c, struct timeval tv);
 int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout);
 int redisContextConnectUnix(redisContext *c, const char *path, struct timeval *timeout);