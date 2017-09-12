@@ -226,7 +226,7 @@ static int cliReadReply(int fd) {
     case '*':
         return cliReadMultiBulkReply(fd);
     default:
-        printf("protocol error, got '%c' as reply type byte\n", type);
+        printf("protocol error, got '%c' as reply type byte", type);
         return 1;
     }
 }
@@ -294,12 +294,8 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         }
 
         retval = cliReadReply(fd);
-        if (retval) {
-            return retval;
-        }
-        if (!config.raw_output && config.tty) {
-            printf("\n");
-        }
+        if (!config.raw_output && config.tty) printf("\n");
+        if (retval) return retval;
     }
     return 0;
 }