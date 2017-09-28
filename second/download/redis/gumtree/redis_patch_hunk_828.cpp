             long port;
 
             if ((getLongFromObjectOrReply(c,c->argv[j+1],
                     &port,NULL) != C_OK))
                 return;
             c->slave_listening_port = port;
+        } else if (!strcasecmp(c->argv[j]->ptr,"ip-address")) {
+            sds ip = c->argv[j+1]->ptr;
+            if (sdslen(ip) < sizeof(c->slave_ip)) {
+                memcpy(c->slave_ip,ip,sdslen(ip)+1);
+            } else {
+                addReplyErrorFormat(c,"REPLCONF ip-address provided by "
+                    "slave instance is too long: %zd bytes", sdslen(ip));
+                return;
+            }
         } else if (!strcasecmp(c->argv[j]->ptr,"capa")) {
             /* Ignore capabilities not understood by this master. */
             if (!strcasecmp(c->argv[j+1]->ptr,"eof"))
                 c->slave_capa |= SLAVE_CAPA_EOF;
         } else if (!strcasecmp(c->argv[j]->ptr,"ack")) {
             /* REPLCONF ACK is used by slave to inform the master the amount
