     if (config.keepalive == 0) {
         printf("WARNING: keepalive disabled, you probably need 'echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse' for Linux and 'sudo sysctl -w net.inet.tcp.msl=1000' for Mac OS X in order to use a lot of clients/requests\n");
     }
 
     if (config.idlemode) {
         printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
-        c = createClient("",0); /* will never receive a reply */
+        c = createClient("",0,NULL); /* will never receive a reply */
         createMissingClients(c);
         aeMain(config.el);
         /* and will wait for every */
     }
 
     /* Run benchmark with command in the remainder of the arguments. */
