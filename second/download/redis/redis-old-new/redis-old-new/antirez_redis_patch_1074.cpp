@@ -2082,8 +2082,15 @@ void clusterCommand(redisClient *c) {
         long port;
 
         /* Perform sanity checks on IP/port */
-        if ((inet_pton(AF_INET,c->argv[0]->ptr,&(((struct sockaddr_in *)&sa)->sin_addr)) ||
-             inet_pton(AF_INET6,c->argv[0]->ptr,&(((struct sockaddr_in6 *)&sa)->sin6_addr))) == 0) {
+        if (inet_pton(AF_INET,c->argv[2]->ptr,
+            &(((struct sockaddr_in *)&sa)->sin_addr)))
+        {
+            sa.ss_family = AF_INET;
+        } else if (inet_pton(AF_INET6,c->argv[2]->ptr,
+            &(((struct sockaddr_in6 *)&sa)->sin6_addr)))
+        {
+            sa.ss_family = AF_INET6;
+        } else {
             addReplyError(c,"Invalid IP address in MEET");
             return;
         }
@@ -2097,9 +2104,17 @@ void clusterCommand(redisClient *c) {
         /* Finally add the node to the cluster with a random name, this 
          * will get fixed in the first handshake (ping/pong). */
         n = createClusterNode(NULL,REDIS_NODE_HANDSHAKE|REDIS_NODE_MEET);
-        sa.ss_family == AF_INET ?
-            inet_ntop(AF_INET,(void*)&(((struct sockaddr_in *)&sa)->sin_addr),n->ip,REDIS_CLUSTER_IPLEN) :
-            inet_ntop(AF_INET6,(void*)&(((struct sockaddr_in6 *)&sa)->sin6_addr),n->ip,REDIS_CLUSTER_IPLEN);
+
+        /* Set node->ip as the normalized string representation of the node
+         * IP address. */
+        if (sa.ss_family == AF_INET)
+            inet_ntop(AF_INET,
+                (void*)&(((struct sockaddr_in *)&sa)->sin_addr),
+                n->ip,REDIS_CLUSTER_IPLEN);
+        else
+            inet_ntop(AF_INET6,
+                (void*)&(((struct sockaddr_in6 *)&sa)->sin6_addr),
+                n->ip,REDIS_CLUSTER_IPLEN);
         n->port = port;
         clusterAddNode(n);
         addReply(c,shared.ok);