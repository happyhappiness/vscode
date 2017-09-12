@@ -2331,7 +2331,7 @@ static int rdbSaveDoubleValue(FILE *fp, double val) {
         len = 1;
         buf[0] = (val < 0) ? 255 : 254;
     } else {
-        snprintf((char*)buf+1,sizeof(buf)-1,"%.16g",val);
+        snprintf((char*)buf+1,sizeof(buf)-1,"%.17g",val);
         buf[0] = strlen((char*)buf);
         len = buf[0]+1;
     }
@@ -4307,7 +4307,7 @@ static void zscoreCommand(redisClient *c) {
                 char buf[128];
                 double *score = dictGetEntryVal(de);
 
-                snprintf(buf,sizeof(buf),"%.16g",*score);
+                snprintf(buf,sizeof(buf),"%.17g",*score);
                 addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n%s\r\n",
                     strlen(buf),buf));
             }