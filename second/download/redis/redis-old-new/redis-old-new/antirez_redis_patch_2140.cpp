@@ -1693,15 +1693,12 @@ static void loadServerConfig(char *filename) {
     char buf[REDIS_CONFIGLINE_MAX+1], *err = NULL;
     int linenum = 0;
     sds line = NULL;
-    char *errormsg = "Fatal error, can't open config file '%s'";
-    char *errorbuf = zmalloc(sizeof(char)*(strlen(errormsg)+strlen(filename)));
-    sprintf(errorbuf, errormsg, filename);
 
     if (filename[0] == '-' && filename[1] == '\0')
         fp = stdin;
     else {
         if ((fp = fopen(filename,"r")) == NULL) {
-            redisLog(REDIS_WARNING, errorbuf);
+            redisLog(REDIS_WARNING, "Fatal error, can't open config file '%s'", filename);
             exit(1);
         }
     }