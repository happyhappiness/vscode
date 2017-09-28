     argv2[2] = sdscatprintf(sdsempty(),"%d",keys);
 
     /* Call it */
     return cliSendCommand(argc+3-got_comma, argv2, config.repeat);
 }
 
+/*------------------------------------------------------------------------------
+ * Latency and latency history modes
+ *--------------------------------------------------------------------------- */
+
 #define LATENCY_SAMPLE_RATE 10 /* milliseconds. */
 #define LATENCY_HISTORY_DEFAULT_INTERVAL 15000 /* milliseconds. */
 static void latencyMode(void) {
     redisReply *reply;
     long long start, latency, min = 0, max = 0, tot = 0, count = 0;
     long long history_interval =
