         score = scores[j];
 
         if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
             unsigned char *eptr;
 
             /* Prefer non-encoded element when dealing with ziplists. */
-            ele = c->argv[3+j*2];
+            ele = c->argv[scoreidx+1+j*2];
             if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
+                if (nx) continue;
                 if (incr) {
                     score += curscore;
                     if (isnan(score)) {
                         addReplyError(c,nanerr);
                         goto cleanup;
                     }
