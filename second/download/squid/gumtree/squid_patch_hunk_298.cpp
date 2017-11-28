     if (theWccp2Connection < 0)
         fatal("Cannot open WCCP Port");
 
 #if defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DONT)
     {
         int i = IP_PMTUDISC_DONT;
-        setsockopt(theWccp2Connection, SOL_IP, IP_MTU_DISCOVER, &i, sizeof i);
+        if (setsockopt(theWccp2Connection, SOL_IP, IP_MTU_DISCOVER, &i, sizeof i) < 0)
+            debugs(80, 2, "WARNING: Path MTU discovery could not be disabled on FD " << theWccp2Connection << ": " << xstrerror());
     }
 
 #endif
-    commSetSelect(theWccp2Connection,
-                  COMM_SELECT_READ,
-                  wccp2HandleUdp,
-                  NULL,
-                  0);
+    Comm::SetSelect(theWccp2Connection, COMM_SELECT_READ, wccp2HandleUdp, NULL, 0);
 
     debugs(80, 1, "Accepting WCCPv2 messages on port " << WCCP_PORT << ", FD " << theWccp2Connection << ".");
     debugs(80, 1, "Initialising all WCCPv2 lists");
 
     /* Initialise all routers on all services */
     memset(&null, 0, sizeof(null));
