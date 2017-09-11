@@ -154,7 +154,7 @@ void feedReplicationBacklogWithObject(robj *o) {
     void *p;
     size_t len;
 
-    if (o->encoding == REDIS_ENCODING_INT) {
+    if (o->encoding == OBJ_ENCODING_INT) {
         len = ll2string(llstr,sizeof(llstr),(long)o->ptr);
         p = llstr;
     } else {
@@ -188,7 +188,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
             int dictid_len;
 
             dictid_len = ll2string(llstr,sizeof(llstr),dictid);
-            selectcmd = createObject(REDIS_STRING,
+            selectcmd = createObject(OBJ_STRING,
                 sdscatprintf(sdsempty(),
                 "*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
                 dictid_len, llstr));
@@ -277,7 +277,7 @@ void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv,
     }
 
     for (j = 0; j < argc; j++) {
-        if (argv[j]->encoding == REDIS_ENCODING_INT) {
+        if (argv[j]->encoding == OBJ_ENCODING_INT) {
             cmdrepr = sdscatprintf(cmdrepr, "\"%ld\"", (long)argv[j]->ptr);
         } else {
             cmdrepr = sdscatrepr(cmdrepr,(char*)argv[j]->ptr,
@@ -287,7 +287,7 @@ void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv,
             cmdrepr = sdscatlen(cmdrepr," ",1);
     }
     cmdrepr = sdscatlen(cmdrepr,"\r\n",2);
-    cmdobj = createObject(REDIS_STRING,cmdrepr);
+    cmdobj = createObject(OBJ_STRING,cmdrepr);
 
     listRewind(monitors,&li);
     while((ln = listNext(&li))) {