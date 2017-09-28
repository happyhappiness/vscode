              * to this node. Instead after the PONG is received and we
              * are no longer in meet/handshake status, we want to send
              * normal PING packets. */
             node->flags &= ~CLUSTER_NODE_MEET;
 
             serverLog(LL_DEBUG,"Connecting with Node %.40s at %s:%d",
-                    node->name, node->ip, node->port+CLUSTER_PORT_INCR);
+                    node->name, node->ip, node->cport);
         }
     }
     dictReleaseIterator(di);
 
     /* Ping some random node 1 time every 10 iterations, so that we usually ping
      * one random node every second. */
