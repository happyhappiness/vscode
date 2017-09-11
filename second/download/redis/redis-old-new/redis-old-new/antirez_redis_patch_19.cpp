@@ -452,13 +452,14 @@ void geoaddCommand(client *c) {
 #define SORT_ASC 1
 #define SORT_DESC 2
 
-#define RADIUS_COORDS 1
-#define RADIUS_MEMBER 2
+#define RADIUS_COORDS (1<<0)    /* Search around coordinates. */
+#define RADIUS_MEMBER (1<<1)    /* Search around member. */
+#define RADIUS_NOSTORE (1<<2)   /* Do not acceot STORE/STOREDIST option. */
 
 /* GEORADIUS key x y radius unit [WITHDIST] [WITHHASH] [WITHCOORD] [ASC|DESC]
  *                               [COUNT count] [STORE key] [STOREDIST key]
  * GEORADIUSBYMEMBER key member radius unit ... options ... */
-void georadiusGeneric(client *c, int type) {
+void georadiusGeneric(client *c, int flags) {
     robj *key = c->argv[1];
     robj *storekey = NULL;
     int storedist = 0; /* 0 for STORE, 1 for STOREDIST. */
@@ -473,19 +474,19 @@ void georadiusGeneric(client *c, int type) {
     /* Find long/lat to use for radius search based on inquiry type */
     int base_args;
     double xy[2] = { 0 };
-    if (type == RADIUS_COORDS) {
+    if (flags & RADIUS_COORDS) {
         base_args = 6;
         if (extractLongLatOrReply(c, c->argv + 2, xy) == C_ERR)
             return;
-    } else if (type == RADIUS_MEMBER) {
+    } else if (flags & RADIUS_MEMBER) {
         base_args = 5;
         robj *member = c->argv[2];
         if (longLatFromMember(zobj, member, xy) == C_ERR) {
             addReplyError(c, "could not decode requested zset member");
             return;
         }
     } else {
-        addReplyError(c, "unknown georadius search type");
+        addReplyError(c, "Unknown georadius search type");
         return;
     }
 
@@ -522,11 +523,17 @@ void georadiusGeneric(client *c, int type) {
                     return;
                 }
                 i++;
-            } else if (!strcasecmp(arg, "store") && (i+1) < remaining) {
+            } else if (!strcasecmp(arg, "store") &&
+                       (i+1) < remaining &&
+                       !(flags & RADIUS_NOSTORE))
+            {
                 storekey = c->argv[base_args+i+1];
                 storedist = 0;
                 i++;
-            } else if (!strcasecmp(arg, "storedist") && (i+1) < remaining) {
+            } else if (!strcasecmp(arg, "storedist") &&
+                       (i+1) < remaining &&
+                       !(flags & RADIUS_NOSTORE))
+            {
                 storekey = c->argv[base_args+i+1];
                 storedist = 1;
                 i++;
@@ -671,10 +678,20 @@ void georadiusCommand(client *c) {
 }
 
 /* GEORADIUSBYMEMBER wrapper function. */
-void georadiusByMemberCommand(client *c) {
+void georadiusbymemberCommand(client *c) {
     georadiusGeneric(c, RADIUS_MEMBER);
 }
 
+/* GEORADIUS_RO wrapper function. */
+void georadiusroCommand(client *c) {
+    georadiusGeneric(c, RADIUS_COORDS|RADIUS_NOSTORE);
+}
+
+/* GEORADIUSBYMEMBER_RO wrapper function. */
+void georadiusbymemberroCommand(client *c) {
+    georadiusGeneric(c, RADIUS_MEMBER|RADIUS_NOSTORE);
+}
+
 /* GEOHASH key ele1 ele2 ... eleN
  *
  * Returns an array with an 11 characters geohash representation of the