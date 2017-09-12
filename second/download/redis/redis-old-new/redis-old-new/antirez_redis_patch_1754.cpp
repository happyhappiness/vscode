@@ -1,8 +1,9 @@
 /* Extracted from anet.c to work properly with Hiredis error reporting.
  *
  * Copyright (c) 2006-2010, Salvatore Sanfilippo <antirez at gmail dot com>
- * All rights reserved.
+ * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
  *
+ * All rights reserved.
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are met:
  *
@@ -43,7 +44,7 @@
 #include <stdarg.h>
 #include <stdio.h>
 
-#include "hiredis.h"
+#include "net.h"
 #include "sds.h"
 
 /* Forward declaration */
@@ -114,7 +115,7 @@ int redisContextConnectTcp(redisContext *c, const char *addr, int port) {
         he = gethostbyname(addr);
         if (he == NULL) {
             __redisSetError(c,REDIS_ERR_OTHER,
-                sdscatprintf(sdsempty(),"can't resolve: %s",addr));
+                sdscatprintf(sdsempty(),"Can't resolve: %s",addr));
             close(s);
             return REDIS_ERR;
         }
@@ -137,6 +138,7 @@ int redisContextConnectTcp(redisContext *c, const char *addr, int port) {
     }
 
     c->fd = s;
+    c->flags |= REDIS_CONNECTED;
     return REDIS_OK;
 }
 
@@ -163,5 +165,6 @@ int redisContextConnectUnix(redisContext *c, const char *path) {
     }
 
     c->fd = s;
+    c->flags |= REDIS_CONNECTED;
     return REDIS_OK;
 }