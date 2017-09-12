@@ -5018,6 +5018,7 @@ static void infoCommand(redisClient *c) {
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"
         "arch_bits:%s\r\n"
+        "multiplexing_api:%s\r\n"
         "uptime_in_seconds:%d\r\n"
         "uptime_in_days:%d\r\n"
         "connected_clients:%d\r\n"
@@ -5031,6 +5032,7 @@ static void infoCommand(redisClient *c) {
         "role:%s\r\n"
         ,REDIS_VERSION,
         (sizeof(long) == 8) ? "64" : "32",
+        aeGetApiName(),
         uptime,
         uptime/(3600*24),
         listLength(server.clients)-listLength(server.slaves),