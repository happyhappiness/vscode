@@ -300,6 +300,7 @@ static int _redisContextConnectTcp(redisContext *c, const char *addr, int port,
                     break;
                 }
             }
+            freeaddrinfo(bservinfo);
             if (!bound) {
                 char buf[128];
                 snprintf(buf,sizeof(buf),"Can't bind socket: %s",strerror(errno));