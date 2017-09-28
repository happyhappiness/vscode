         listRewind(server.slowlog,&li);
         totentries = addDeferredMultiBulkLength(c);
         while(count-- && (ln = listNext(&li))) {
             int j;
 
             se = ln->value;
-            addReplyMultiBulkLen(c,4);
+            addReplyMultiBulkLen(c,6);
             addReplyLongLong(c,se->id);
             addReplyLongLong(c,se->time);
             addReplyLongLong(c,se->duration);
             addReplyMultiBulkLen(c,se->argc);
             for (j = 0; j < se->argc; j++)
                 addReplyBulk(c,se->argv[j]);
+            addReplyBulkCBuffer(c,se->peerid,sdslen(se->peerid));
+            addReplyBulkCBuffer(c,se->cname,sdslen(se->cname));
             sent++;
         }
         setDeferredMultiBulkLength(c,totentries,sent);
     } else {
         addReplyError(c,
             "Unknown SLOWLOG subcommand or wrong # of args. Try GET, RESET, LEN.");
