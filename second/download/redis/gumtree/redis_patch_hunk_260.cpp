         if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                 == NULL) return;
         addReplyBulkCString(c,strEncoding(o->encoding));
     } else if (!strcasecmp(c->argv[1]->ptr,"idletime") && c->argc == 3) {
         if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                 == NULL) return;
-        addReplyLongLong(c,estimateObjectIdleTime(o));
+        addReplyLongLong(c,estimateObjectIdleTime(o)/1000);
     } else {
         addReplyError(c,"Syntax error. Try OBJECT (refcount|encoding|idletime)");
     }
 }
 
