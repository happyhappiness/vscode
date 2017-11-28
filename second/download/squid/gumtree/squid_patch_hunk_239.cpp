                           e->host,
                           e->http_port,
                           e->icp.port);
         storeAppendPrintf(sentry, "Flags      :");
         dump_peer_options(sentry, e);
 
-        for (i = 0; i < e->n_addresses; i++) {
+        for (i = 0; i < e->n_addresses; ++i) {
             storeAppendPrintf(sentry, "Address[%d] : %s\n", i,
                               e->addresses[i].NtoA(ntoabuf,MAX_IPSTRLEN) );
         }
 
         storeAppendPrintf(sentry, "Status     : %s\n",
                           neighborUp(e) ? "Up" : "Down");
