@@ -977,16 +977,11 @@ void createSharedObjects(void) {
     shared.space = createObject(REDIS_STRING,sdsnew(" "));
     shared.colon = createObject(REDIS_STRING,sdsnew(":"));
     shared.plus = createObject(REDIS_STRING,sdsnew("+"));
-    shared.select0 = createStringObject("select 0\r\n",10);
-    shared.select1 = createStringObject("select 1\r\n",10);
-    shared.select2 = createStringObject("select 2\r\n",10);
-    shared.select3 = createStringObject("select 3\r\n",10);
-    shared.select4 = createStringObject("select 4\r\n",10);
-    shared.select5 = createStringObject("select 5\r\n",10);
-    shared.select6 = createStringObject("select 6\r\n",10);
-    shared.select7 = createStringObject("select 7\r\n",10);
-    shared.select8 = createStringObject("select 8\r\n",10);
-    shared.select9 = createStringObject("select 9\r\n",10);
+
+    for (j = 0; j < REDIS_SHARED_SELECT_CMDS; j++) {
+        shared.select[j] = createObject(REDIS_STRING,
+            sdscatprintf(sdsempty(),"select %d\r\n", j));
+    }
     shared.messagebulk = createStringObject("$7\r\nmessage\r\n",13);
     shared.pmessagebulk = createStringObject("$8\r\npmessage\r\n",14);
     shared.subscribebulk = createStringObject("$9\r\nsubscribe\r\n",15);