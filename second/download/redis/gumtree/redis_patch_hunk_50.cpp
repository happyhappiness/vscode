                     (int)(server.unixtime-server.repl_transfer_lastio)
                 );
             }
 
             if (server.repl_state != REDIS_REPL_CONNECTED) {
                 info = sdscatprintf(info,
-                    "master_link_down_since_seconds:%ld\r\n",
-                    (long)server.unixtime-server.repl_down_since);
+                    "master_link_down_since_seconds:%jd\r\n",
+                    (intmax_t)server.unixtime-server.repl_down_since);
             }
             info = sdscatprintf(info,
                 "slave_priority:%d\r\n"
                 "slave_read_only:%d\r\n",
                 server.slave_priority,
                 server.repl_slave_ro);
