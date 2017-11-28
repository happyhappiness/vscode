         debugs(31, DBG_IMPORTANT, "HTCP Disabled.");
         return;
     }
 
     htcpIncomingConn = new Comm::Connection;
     htcpIncomingConn->local = Config.Addrs.udp_incoming;
-    htcpIncomingConn->local.SetPort(Config.Port.htcp);
+    htcpIncomingConn->local.port(Config.Port.htcp);
 
-    if (!Ip::EnableIpv6 && !htcpIncomingConn->local.SetIPv4()) {
+    if (!Ip::EnableIpv6 && !htcpIncomingConn->local.setIPv4()) {
         debugs(31, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << htcpIncomingConn->local << " is not an IPv4 address.");
         fatal("HTCP port cannot be opened.");
     }
     /* split-stack for now requires default IPv4-only HTCP */
-    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && htcpIncomingConn->local.IsAnyAddr()) {
-        htcpIncomingConn->local.SetIPv4();
+    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && htcpIncomingConn->local.isAnyAddr()) {
+        htcpIncomingConn->local.setIPv4();
     }
 
     AsyncCall::Pointer call = asyncCall(31, 2,
                                         "htcpIncomingConnectionOpened",
                                         Comm::UdpOpenDialer(&htcpIncomingConnectionOpened));
 
     Ipc::StartListening(SOCK_DGRAM,
                         IPPROTO_UDP,
                         htcpIncomingConn,
                         Ipc::fdnInHtcpSocket, call);
 
-    if (!Config.Addrs.udp_outgoing.IsNoAddr()) {
+    if (!Config.Addrs.udp_outgoing.isNoAddr()) {
         htcpOutgoingConn = new Comm::Connection;
         htcpOutgoingConn->local = Config.Addrs.udp_outgoing;
-        htcpOutgoingConn->local.SetPort(Config.Port.htcp);
+        htcpOutgoingConn->local.port(Config.Port.htcp);
 
-        if (!Ip::EnableIpv6 && !htcpOutgoingConn->local.SetIPv4()) {
+        if (!Ip::EnableIpv6 && !htcpOutgoingConn->local.setIPv4()) {
             debugs(31, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << htcpOutgoingConn->local << " is not an IPv4 address.");
             fatal("HTCP port cannot be opened.");
         }
         /* split-stack for now requires default IPv4-only HTCP */
-        if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && htcpOutgoingConn->local.IsAnyAddr()) {
-            htcpOutgoingConn->local.SetIPv4();
+        if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && htcpOutgoingConn->local.isAnyAddr()) {
+            htcpOutgoingConn->local.setIPv4();
         }
 
         enter_suid();
         comm_open_listener(SOCK_DGRAM, IPPROTO_UDP, htcpOutgoingConn, "Outgoing HTCP Socket");
         leave_suid();
 
