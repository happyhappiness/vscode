@@ -394,23 +394,26 @@ static sds cliFormatReplyRaw(redisReply *r) {
     switch (r->type) {
     case REDIS_REPLY_NIL:
         /* Nothing... */
-    break;
+        break;
     case REDIS_REPLY_ERROR:
+        out = sdscatlen(out,r->str,r->len);
+        out = sdscatlen(out,"\n",1);
+        break;
     case REDIS_REPLY_STATUS:
     case REDIS_REPLY_STRING:
         out = sdscatlen(out,r->str,r->len);
-    break;
+        break;
     case REDIS_REPLY_INTEGER:
         out = sdscatprintf(out,"%lld",r->integer);
-    break;
+        break;
     case REDIS_REPLY_ARRAY:
         for (i = 0; i < r->elements; i++) {
             if (i > 0) out = sdscat(out,config.mb_delim);
             tmp = cliFormatReplyRaw(r->element[i]);
             out = sdscatlen(out,tmp,sdslen(tmp));
             sdsfree(tmp);
         }
-    break;
+        break;
     default:
         fprintf(stderr,"Unknown reply type: %d\n", r->type);
         exit(1);
@@ -464,7 +467,18 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         return REDIS_OK;
     }
 
-    output_raw = !strcasecmp(command,"info");
+    output_raw = 0;
+    if (!strcasecmp(command,"info") ||
+        (argc == 2 && !strcasecmp(command,"cluster") &&
+                      (!strcasecmp(argv[1],"nodes") ||
+                       !strcasecmp(argv[1],"info"))) ||
+        (argc == 2 && !strcasecmp(command,"client") &&
+                       !strcasecmp(argv[1],"list")))
+
+    {
+        output_raw = 1;
+    }
+
     if (!strcasecmp(command,"help") || !strcasecmp(command,"?")) {
         cliOutputHelp(--argc, ++argv);
         return REDIS_OK;