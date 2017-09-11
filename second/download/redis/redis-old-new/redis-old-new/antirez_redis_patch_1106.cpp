@@ -2075,11 +2075,12 @@ void clusterCommand(redisClient *c) {
     if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
         /* CLUSTER MEET <ip> <port> */
         clusterNode *n;
-        struct sockaddr_in sa;
+        struct sockaddr_storage sa;
         long port;
 
         /* Perform sanity checks on IP/port */
-        if (inet_pton(AF_INET,c->argv[0]->ptr,&(sa.sin_addr)) == 0) {
+        if ((inet_pton(AF_INET,c->argv[0]->ptr,&(((struct sockaddr_in *)&sa)->sin_addr)) ||
+             inet_pton(AF_INET6,c->argv[0]->ptr,&(((struct sockaddr_in6 *)&sa)->sin6_addr))) == 0) {
             addReplyError(c,"Invalid IP address in MEET");
             return;
         }
@@ -2093,7 +2094,9 @@ void clusterCommand(redisClient *c) {
         /* Finally add the node to the cluster with a random name, this 
          * will get fixed in the first handshake (ping/pong). */
         n = createClusterNode(NULL,REDIS_NODE_HANDSHAKE|REDIS_NODE_MEET);
-        inet_ntop(sa.sin_family,(void*)&(sa.sin_addr),n->ip,REDIS_CLUSTER_IPLEN);
+        sa.ss_family == AF_INET ?
+            inet_ntop(AF_INET,(void*)&(((struct sockaddr_in *)&sa)->sin_addr),n->ip,REDIS_CLUSTER_IPLEN) :
+            inet_ntop(AF_INET6,(void*)&(((struct sockaddr_in6 *)&sa)->sin6_addr),n->ip,REDIS_CLUSTER_IPLEN);
         n->port = port;
         clusterAddNode(n);
         addReply(c,shared.ok);