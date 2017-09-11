@@ -758,7 +758,7 @@ void replconfCommand(client *c) {
             /* REPLCONF GETACK is used in order to request an ACK ASAP
              * to the slave. */
             if (server.masterhost && server.master) replicationSendAck();
-            /* Note: this command does not reply anything! */
+            return;
         } else {
             addReplyErrorFormat(c,"Unrecognized REPLCONF option: %s",
                 (char*)c->argv[j]->ptr);