                           e->icp.port);
         storeAppendPrintf(sentry, "Flags      :");
         dump_peer_options(sentry, e);
 
         for (i = 0; i < e->n_addresses; ++i) {
             storeAppendPrintf(sentry, "Address[%d] : %s\n", i,
-                              e->addresses[i].NtoA(ntoabuf,MAX_IPSTRLEN) );
+                              e->addresses[i].toStr(ntoabuf,MAX_IPSTRLEN) );
         }
 
         storeAppendPrintf(sentry, "Status     : %s\n",
                           neighborUp(e) ? "Up" : "Down");
         storeAppendPrintf(sentry, "FETCHES    : %d\n", e->stats.fetches);
         storeAppendPrintf(sentry, "OPEN CONNS : %d\n", e->stats.conn_open);
