@@ -61,8 +61,14 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
                 selectcmd = shared.select[dictid];
                 incrRefCount(selectcmd);
             } else {
+                char dictid_str[64];
+                int dictid_len;
+
+                dictid_len = ll2string(dictid_str,sizeof(dictid_str),dictid);
                 selectcmd = createObject(REDIS_STRING,
-                    sdscatprintf(sdsempty(),"select %d\r\n",dictid));
+                    sdscatprintf(sdsempty(),
+                        "*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
+                        dictid_len, dictid_str));
             }
             addReply(slave,selectcmd);
             decrRefCount(selectcmd);