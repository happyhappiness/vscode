@@ -92,22 +92,22 @@ sds keyspaceEventsFlagsToString(int flags) {
  * 'dbid' is the database ID where the key lives.  */
 void notifyKeyspaceEvent(int type, char *event, robj *key, int dbid) {
     sds chan;
-    robj *chanobj;
+    robj *chanobj, *eventobj;
     int len = -1;
     char buf[24];
 
     /* If notifications for this class of events are off, return ASAP. */
     if (!(server.notify_keyspace_events & type)) return;
 
+    eventobj = createStringObject(event,strlen(event));
+
     /* __keyspace@<db>__:<key> <event> notifications. */
     if (server.notify_keyspace_events & REDIS_NOTIFY_KEYSPACE) {
-        robj *eventobj;
-
         chan = sdsnewlen("__keyspace@",11);
         len = ll2string(buf,sizeof(buf),dbid);
         chan = sdscatlen(chan, buf, len);
         chan = sdscatlen(chan, "__:", 3);
-        eventobj = createStringObject(event,strlen(event));
+        chan = sdscatsds(chan, key->ptr);
         chanobj = createObject(REDIS_STRING, chan);
         pubsubPublishMessage(chanobj, eventobj);
         decrRefCount(chanobj);
@@ -119,8 +119,10 @@ void notifyKeyspaceEvent(int type, char *event, robj *key, int dbid) {
         if (len == -1) len = ll2string(buf,sizeof(buf),dbid);
         chan = sdscatlen(chan, buf, len);
         chan = sdscatlen(chan, "__:", 3);
+        chan = sdscatsds(chan, eventobj->ptr);
         chanobj = createObject(REDIS_STRING, chan);
         pubsubPublishMessage(chanobj, key);
         decrRefCount(chanobj);
     }
+    decrRefCount(eventobj);
 }