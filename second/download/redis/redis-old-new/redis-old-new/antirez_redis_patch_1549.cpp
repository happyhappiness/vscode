@@ -646,8 +646,9 @@ struct redisServer {
     int cluster_enabled;
     clusterState cluster;
     /* Scripting */
-    lua_State *lua;
-    redisClient *lua_client;
+    lua_State *lua; /* The Lua interpreter. We use just one for all clients */
+    redisClient *lua_client; /* The "fake client" to query Redis from Lua */
+    dict *lua_scripts; /* A dictionary of SHA1 -> Lua scripts */
     long long lua_time_limit;
     long long lua_time_start;
 };
@@ -742,6 +743,7 @@ extern struct sharedObjectsStruct shared;
 extern dictType setDictType;
 extern dictType zsetDictType;
 extern dictType clusterNodesDictType;
+extern dictType dbDictType;
 extern double R_Zero, R_PosInf, R_NegInf, R_Nan;
 dictType hashDictType;
 
@@ -782,6 +784,7 @@ void *dupClientReplyValue(void *o);
 void getClientsMaxBuffers(unsigned long *longest_output_list,
                           unsigned long *biggest_input_buffer);
 void rewriteClientCommandVector(redisClient *c, int argc, ...);
+void rewriteClientCommandArgument(redisClient *c, int i, robj *newval);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
@@ -821,6 +824,7 @@ void touchWatchedKeysOnFlush(int dbid);
 /* Redis object implementation */
 void decrRefCount(void *o);
 void incrRefCount(robj *o);
+robj *resetRefCount(robj *obj);
 void freeStringObject(robj *o);
 void freeListObject(robj *o);
 void freeSetObject(robj *o);