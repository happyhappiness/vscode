         close(cs->fd);
         zfree(cs);
         dictDelete(server.migrate_cached_sockets,dictGetKey(de));
     }
 
     /* Create the socket */
-    fd = anetTcpNonBlockBindConnect(server.neterr,c->argv[1]->ptr,
-                atoi(c->argv[2]->ptr),REDIS_BIND_ADDR);
+    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
+                                atoi(c->argv[2]->ptr));
     if (fd == -1) {
         sdsfree(name);
         addReplyErrorFormat(c,"Can't connect to target node: %s",
             server.neterr);
         return NULL;
     }
