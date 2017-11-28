 
     if (theWccpConnection < 0)
         fatal("Cannot open WCCP Port");
 
     Comm::SetSelect(theWccpConnection, COMM_SELECT_READ, wccpHandleUdp, NULL, 0);
 
-    debugs(80, 1, "Accepting WCCPv1 messages on " << Config.Wccp.address << ", FD " << theWccpConnection << ".");
-
+    debugs(80, DBG_IMPORTANT, "Accepting WCCPv1 messages on " << Config.Wccp.address << ", FD " << theWccpConnection << ".");
 
     // Sadly WCCP only does IPv4
 
     struct sockaddr_in router;
     Config.Wccp.router.GetSockAddr(router);
     if (connect(theWccpConnection, (struct sockaddr*)&router, sizeof(router)))
