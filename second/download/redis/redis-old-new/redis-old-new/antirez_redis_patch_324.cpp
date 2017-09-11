@@ -463,7 +463,7 @@ static sds cliFormatReplyTTY(redisReply *r, char *prefix) {
             _prefix = sdscat(sdsnew(prefix),_prefixlen);
 
             /* Setup prefix format for every entry */
-            snprintf(_prefixfmt,sizeof(_prefixfmt),"%%s%%%dd) ",idxlen);
+            snprintf(_prefixfmt,sizeof(_prefixfmt),"%%s%%%ud) ",idxlen);
 
             for (i = 0; i < r->elements; i++) {
                 /* Don't use the prefix for the first element, as the parent
@@ -2050,7 +2050,7 @@ void bytesToHuman(char *s, long long n) {
     }
     if (n < 1024) {
         /* Bytes */
-        sprintf(s,"%lluB",n);
+        sprintf(s,"%lldB",n);
         return;
     } else if (n < (1024*1024)) {
         d = (double)n/(1024);