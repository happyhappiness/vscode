                 if (slave->replstate == SLAVE_STATE_ONLINE)
                     lag = time(NULL) - slave->repl_ack_time;
 
                 info = sdscatprintf(info,
                     "slave%d:ip=%s,port=%d,state=%s,"
                     "offset=%lld,lag=%ld\r\n",
-                    slaveid,ip,slave->slave_listening_port,state,
+                    slaveid,slaveip,slave->slave_listening_port,state,
                     slave->repl_ack_off, lag);
                 slaveid++;
             }
         }
         info = sdscatprintf(info,
             "master_repl_offset:%lld\r\n"
