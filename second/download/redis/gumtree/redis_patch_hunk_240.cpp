              * already successfully promoted. So as the address of this slave
              * we use the old master address instead. */
             if (sentinelAddrIsEqual(slave_addr,master_addr))
                 slave_addr = master->addr;
             line = sdscatprintf(sdsempty(),
                 "sentinel known-slave %s %s %d",
-                master->name, ri->addr->ip, ri->addr->port);
+                master->name, slave_addr->ip, slave_addr->port);
             rewriteConfigRewriteLine(state,"sentinel",line,1);
         }
         dictReleaseIterator(di2);
 
         /* sentinel known-sentinel */
         di2 = dictGetIterator(master->sentinels);
