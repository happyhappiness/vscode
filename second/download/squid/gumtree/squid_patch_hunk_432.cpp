                                   COMM_NONBLOCKING,
                                   "Multicast Miss Stream");
 
         if (mcast_miss_fd < 0)
             fatal("Cannot open Multicast Miss Stream Socket");
 
-        debugs(46, 1, "Multicast Miss Stream Socket opened on FD " << mcast_miss_fd);
+        debugs(46, DBG_IMPORTANT, "Multicast Miss Stream Socket opened on FD " << mcast_miss_fd);
 
         mcastSetTtl(mcast_miss_fd, Config.mcast_miss.ttl);
 
         if (strlen(Config.mcast_miss.encode_key) < 16)
             fatal("mcast_encode_key is too short, must be 16 characters");
     }
