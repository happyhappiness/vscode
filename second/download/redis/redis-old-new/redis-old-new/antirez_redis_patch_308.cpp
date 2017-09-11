@@ -1678,7 +1678,7 @@ void enableWatchdog(int period);
 void disableWatchdog(void);
 void watchdogScheduleSignal(int period);
 void serverLogHexDump(int level, char *descr, void *value, size_t len);
-int memtest_test(unsigned long *m, size_t bytes, int passes, int interactive);
+int memtest_preserving_test(unsigned long *m, size_t bytes, int passes);
 
 #define redisDebug(fmt, ...) \
     printf("DEBUG %s:%d > " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)