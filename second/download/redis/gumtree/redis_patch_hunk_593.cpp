     dictEmpty(server.commands,NULL);
     for (j = 0; j < sizeof(sentinelcmds)/sizeof(sentinelcmds[0]); j++) {
         int retval;
         struct redisCommand *cmd = sentinelcmds+j;
 
         retval = dictAdd(server.commands, sdsnew(cmd->name), cmd);
-        redisAssert(retval == DICT_OK);
+        serverAssert(retval == DICT_OK);
     }
 
     /* Initialize various data structures. */
     sentinel.current_epoch = 0;
     sentinel.masters = dictCreate(&instancesDictType,NULL);
     sentinel.tilt = 0;
     sentinel.tilt_start_time = 0;
     sentinel.previous_time = mstime();
     sentinel.running_scripts = 0;
     sentinel.scripts_queue = listCreate();
     sentinel.announce_ip = NULL;
     sentinel.announce_port = 0;
+    sentinel.simfailure_flags = SENTINEL_SIMFAILURE_NONE;
+    memset(sentinel.myid,0,sizeof(sentinel.myid));
 }
 
 /* This function gets called when the server is in Sentinel mode, started,
  * loaded the configuration, and is ready for normal operations. */
 void sentinelIsRunning(void) {
-    redisLog(REDIS_WARNING,"Sentinel runid is %s", server.runid);
+    int j;
 
     if (server.configfile == NULL) {
-        redisLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Sentinel started without a config file. Exiting...");
         exit(1);
     } else if (access(server.configfile,W_OK) == -1) {
-        redisLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Sentinel config file %s is not writable: %s. Exiting...",
             server.configfile,strerror(errno));
         exit(1);
     }
 
+    /* If this Sentinel has yet no ID set in the configuration file, we
+     * pick a random one and persist the config on disk. From now on this
+     * will be this Sentinel ID across restarts. */
+    for (j = 0; j < CONFIG_RUN_ID_SIZE; j++)
+        if (sentinel.myid[j] != 0) break;
+
+    if (j == CONFIG_RUN_ID_SIZE) {
+        /* Pick ID and presist the config. */
+        getRandomHexChars(sentinel.myid,CONFIG_RUN_ID_SIZE);
+        sentinelFlushConfig();
+    }
+
+    /* Log its ID to make debugging of issues simpler. */
+    serverLog(LL_WARNING,"Sentinel ID is %s", sentinel.myid);
+
     /* We want to generate a +monitor event for every configured master
      * at startup. */
     sentinelGenerateInitialMonitorEvents();
 }
 
 /* ============================== sentinelAddr ============================== */
