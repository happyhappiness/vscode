@@ -3706,9 +3706,7 @@ int main(int argc, char **argv) {
         sdsfree(options);
     }
 
-//    serverLog(LL_WARNING, "_.~\"(_.~\"(_.~\"(_.~\"(_.~\"( Redis is starting...");
     serverLog(LL_WARNING, "oO0OoO0OoO0Oo Redis is starting oO0OoO0OoO0Oo");
-
     serverLog(LL_WARNING,
         "Redis version=%s, bits=%d, commit=%s, modified=%d, pid=%d, just started",
             REDIS_VERSION,