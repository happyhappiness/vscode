                                            COMM_NONBLOCKING,
                                            "WCCP Socket");
 
     if (theWccpConnection < 0)
         fatal("Cannot open WCCP Port");
 
-    commSetSelect(theWccpConnection,
-                  COMM_SELECT_READ,
-                  wccpHandleUdp,
-                  NULL,
-                  0);
+    Comm::SetSelect(theWccpConnection, COMM_SELECT_READ, wccpHandleUdp, NULL, 0);
 
     debugs(80, 1, "Accepting WCCPv1 messages on " << Config.Wccp.address << ", FD " << theWccpConnection << ".");
 
-    Config.Wccp.router.GetAddrInfo(router,AF_INET);
 
-    if (connect(theWccpConnection, router->ai_addr, router->ai_addrlen))
-        fatal("Unable to connect WCCP out socket");
+    // Sadly WCCP only does IPv4
 
-    Config.Wccp.router.FreeAddrInfo(router);
-
-    Config.Wccp.address.InitAddrInfo(local);
+    struct sockaddr_in router;
+    Config.Wccp.router.GetSockAddr(router);
+    if (connect(theWccpConnection, (struct sockaddr*)&router, sizeof(router)))
+        fatal("Unable to connect WCCP out socket");
 
-    if (getsockname(theWccpConnection, local->ai_addr, &local->ai_addrlen))
+    struct sockaddr_in local;
+    memset(&local, '\0', sizeof(local));
+    socklen_t slen = sizeof(local);
+    if (getsockname(theWccpConnection, (struct sockaddr*)&local, &slen))
         fatal("Unable to getsockname on WCCP out socket");
 
-    local_ip = *local;
-
-    Config.Wccp.address.FreeAddrInfo(local);
+    local_ip = local;
 }
 
 
 void
 wccpConnectionClose(void)
 {
