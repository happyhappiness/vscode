              * the slave online when the first ACK is received (which
              * confirms slave is online and ready to get more data). */
             if (c->repl_put_online_on_ack && c->replstate == REDIS_REPL_ONLINE)
                 putSlaveOnline(c);
             /* Note: this command does not reply anything! */
             return;
+        } else if (!strcasecmp(c->argv[j]->ptr,"getack")) {
+            /* REPLCONF GETACK is used in order to request an ACK ASAP
+             * to the slave. */
+            if (server.masterhost && server.master) replicationSendAck();
+            /* Note: this command does not reply anything! */
         } else {
             addReplyErrorFormat(c,"Unrecognized REPLCONF option: %s",
                 (char*)c->argv[j]->ptr);
             return;
         }
     }
