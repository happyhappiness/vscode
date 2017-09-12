@@ -157,22 +157,18 @@ static sds cliFormatReply(redisReply *r, char *prefix) {
     sds out = sdsempty();
     switch (r->type) {
     case REDIS_REPLY_ERROR:
-        out = sdscat(out,prefix);
         if (config.tty) out = sdscat(out,"(error) ");
         out = sdscatprintf(out,"%s\n", r->str);
     break;
     case REDIS_REPLY_STATUS:
-        out = sdscat(out,prefix);
         out = sdscat(out,r->str);
         out = sdscat(out,"\n");
     break;
     case REDIS_REPLY_INTEGER:
-        out = sdscat(out,prefix);
         if (config.tty) out = sdscat(out,"(integer) ");
         out = sdscatprintf(out,"%lld\n",r->integer);
     break;
     case REDIS_REPLY_STRING:
-        out = sdscat(out,prefix);
         if (config.raw_output || !config.tty) {
             out = sdscatlen(out,r->str,r->len);
         } else {
@@ -183,23 +179,44 @@ static sds cliFormatReply(redisReply *r, char *prefix) {
         }
     break;
     case REDIS_REPLY_NIL:
-        out = sdscat(out,prefix);
         out = sdscat(out,"(nil)\n");
     break;
     case REDIS_REPLY_ARRAY:
         if (r->elements == 0) {
-            out = sdscat(out,prefix);
             out = sdscat(out,"(empty list or set)\n");
         } else {
-            unsigned int i;
+            unsigned int i, idxlen = 0;
+            char _prefixlen[16];
+            char _prefixfmt[16];
+            sds _prefix;
             sds tmp;
 
+            /* Calculate chars needed to represent the largest index */
+            i = r->elements;
+            do {
+                idxlen++;
+                i /= 10;
+            } while(i);
+
+            /* Prefix for nested multi bulks should grow with idxlen+2 spaces */
+            memset(_prefixlen,' ',idxlen+2);
+            _prefixlen[idxlen+2] = '\0';
+            _prefix = sdscat(sdsnew(prefix),_prefixlen);
+
+            /* Setup prefix format for every entry */
+            snprintf(_prefixfmt,sizeof(_prefixfmt),"%%s%%%dd) ",idxlen);
+
             for (i = 0; i < r->elements; i++) {
-                tmp = cliFormatReply(r->element[i],prefix);
-                out = sdscat(out,prefix);
+                /* Don't use the prefix for the first element, as the parent
+                 * caller already prepended the index number. */
+                out = sdscatprintf(out,_prefixfmt,i == 0 ? "" : prefix,i+1);
+
+                /* Format the multi bulk entry */
+                tmp = cliFormatReply(r->element[i],_prefix);
                 out = sdscatlen(out,tmp,sdslen(tmp));
                 sdsfree(tmp);
             }
+            sdsfree(_prefix);
         }
     break;
     default: