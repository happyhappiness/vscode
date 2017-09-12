@@ -172,11 +172,8 @@
 
 /* Sort operations */
 #define REDIS_SORT_GET 0
-#define REDIS_SORT_DEL 1
-#define REDIS_SORT_INCR 2
-#define REDIS_SORT_DECR 3
-#define REDIS_SORT_ASC 4
-#define REDIS_SORT_DESC 5
+#define REDIS_SORT_ASC 1
+#define REDIS_SORT_DESC 2
 #define REDIS_SORTKEY_MAX 1024
 
 /* Log levels */
@@ -4447,7 +4444,7 @@ static void sortCommand(redisClient *c) {
     int limit_start = 0, limit_count = -1, start, end;
     int j, dontsort = 0, vectorlen;
     int getop = 0; /* GET operation counter */
-    robj *sortval, *sortby = NULL;
+    robj *sortval, *sortby = NULL, *storekey = NULL;
     redisSortObject *vector; /* Resulting vector to sort */
 
     /* Lookup the key to sort. It must be of the right types */
@@ -4485,6 +4482,9 @@ static void sortCommand(redisClient *c) {
             limit_start = atoi(c->argv[j+1]->ptr);
             limit_count = atoi(c->argv[j+2]->ptr);
             j+=2;
+        } else if (!strcasecmp(c->argv[j]->ptr,"store") && leftargs >= 1) {
+            storekey = c->argv[j+1];
+            j++;
         } else if (!strcasecmp(c->argv[j]->ptr,"by") && leftargs >= 1) {
             sortby = c->argv[j+1];
             /* If the BY pattern does not contain '*', i.e. it is constant,
@@ -4496,18 +4496,6 @@ static void sortCommand(redisClient *c) {
                 REDIS_SORT_GET,c->argv[j+1]));
             getop++;
             j++;
-        } else if (!strcasecmp(c->argv[j]->ptr,"del") && leftargs >= 1) {
-            listAddNodeTail(operations,createSortOperation(
-                REDIS_SORT_DEL,c->argv[j+1]));
-            j++;
-        } else if (!strcasecmp(c->argv[j]->ptr,"incr") && leftargs >= 1) {
-            listAddNodeTail(operations,createSortOperation(
-                REDIS_SORT_INCR,c->argv[j+1]));
-            j++;
-        } else if (!strcasecmp(c->argv[j]->ptr,"get") && leftargs >= 1) {
-            listAddNodeTail(operations,createSortOperation(
-                REDIS_SORT_DECR,c->argv[j+1]));
-            j++;
         } else {
             decrRefCount(sortval);
             listRelease(operations);
@@ -4614,32 +4602,70 @@ static void sortCommand(redisClient *c) {
     /* Send command output to the output buffer, performing the specified
      * GET/DEL/INCR/DECR operations if any. */
     outputlen = getop ? getop*(end-start+1) : end-start+1;
-    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
-    for (j = start; j <= end; j++) {
-        listNode *ln;
-        if (!getop) {
-            addReplyBulkLen(c,vector[j].obj);
-            addReply(c,vector[j].obj);
-            addReply(c,shared.crlf);
+    if (storekey == NULL) {
+        /* STORE option not specified, sent the sorting result to client */
+        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
+        for (j = start; j <= end; j++) {
+            listNode *ln;
+            if (!getop) {
+                addReplyBulkLen(c,vector[j].obj);
+                addReply(c,vector[j].obj);
+                addReply(c,shared.crlf);
+            }
+            listRewind(operations);
+            while((ln = listYield(operations))) {
+                redisSortOperation *sop = ln->value;
+                robj *val = lookupKeyByPattern(c->db,sop->pattern,
+                    vector[j].obj);
+
+                if (sop->type == REDIS_SORT_GET) {
+                    if (!val || val->type != REDIS_STRING) {
+                        addReply(c,shared.nullbulk);
+                    } else {
+                        addReplyBulkLen(c,val);
+                        addReply(c,val);
+                        addReply(c,shared.crlf);
+                    }
+                } else {
+                    assert(sop->type == REDIS_SORT_GET); /* always fails */
+                }
+            }
         }
-        listRewind(operations);
-        while((ln = listYield(operations))) {
-            redisSortOperation *sop = ln->value;
-            robj *val = lookupKeyByPattern(c->db,sop->pattern,
-                vector[j].obj);
-
-            if (sop->type == REDIS_SORT_GET) {
-                if (!val || val->type != REDIS_STRING) {
-                    addReply(c,shared.nullbulk);
+    } else {
+        robj *listObject = createListObject();
+        list *listPtr = (list*) listObject->ptr;
+
+        /* STORE option specified, set the sorting result as a List object */
+        for (j = start; j <= end; j++) {
+            listNode *ln;
+            if (!getop) {
+                listAddNodeTail(listPtr,vector[j].obj);
+                incrRefCount(vector[j].obj);
+            }
+            listRewind(operations);
+            while((ln = listYield(operations))) {
+                redisSortOperation *sop = ln->value;
+                robj *val = lookupKeyByPattern(c->db,sop->pattern,
+                    vector[j].obj);
+
+                if (sop->type == REDIS_SORT_GET) {
+                    if (!val || val->type != REDIS_STRING) {
+                        listAddNodeTail(listPtr,createStringObject("",0));
+                    } else {
+                        listAddNodeTail(listPtr,val);
+                        incrRefCount(val);
+                    }
                 } else {
-                    addReplyBulkLen(c,val);
-                    addReply(c,val);
-                    addReply(c,shared.crlf);
+                    assert(sop->type == REDIS_SORT_GET); /* always fails */
                 }
-            } else if (sop->type == REDIS_SORT_DEL) {
-                /* TODO */
             }
         }
+        dictReplace(c->db->dict,storekey,listObject);
+        /* Note: we add 1 because the DB is dirty anyway since even if the
+         * SORT result is empty a new key is set and maybe the old content
+         * replaced. */
+        server.dirty += 1+outputlen;
+        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",outputlen));
     }
 
     /* Cleanup */