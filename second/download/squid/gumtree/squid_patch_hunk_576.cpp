 
     if ((port = Config.Port.icp) <= 0)
         return;
 
     icpIncomingConn = new Comm::Connection;
     icpIncomingConn->local = Config.Addrs.udp_incoming;
-    icpIncomingConn->local.SetPort(port);
+    icpIncomingConn->local.port(port);
 
-    if (!Ip::EnableIpv6 && !icpIncomingConn->local.SetIPv4()) {
+    if (!Ip::EnableIpv6 && !icpIncomingConn->local.setIPv4()) {
         debugs(12, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << icpIncomingConn->local << " is not an IPv4 address.");
         fatal("ICP port cannot be opened.");
     }
     /* split-stack for now requires default IPv4-only ICP */
-    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && icpIncomingConn->local.IsAnyAddr()) {
-        icpIncomingConn->local.SetIPv4();
+    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && icpIncomingConn->local.isAnyAddr()) {
+        icpIncomingConn->local.setIPv4();
     }
 
     AsyncCall::Pointer call = asyncCall(12, 2,
                                         "icpIncomingConnectionOpened",
                                         Comm::UdpOpenDialer(&icpIncomingConnectionOpened));
 
     Ipc::StartListening(SOCK_DGRAM,
                         IPPROTO_UDP,
                         icpIncomingConn,
                         Ipc::fdnInIcpSocket, call);
 
-    if ( !Config.Addrs.udp_outgoing.IsNoAddr() ) {
+    if ( !Config.Addrs.udp_outgoing.isNoAddr() ) {
         icpOutgoingConn = new Comm::Connection;
         icpOutgoingConn->local = Config.Addrs.udp_outgoing;
-        icpOutgoingConn->local.SetPort(port);
+        icpOutgoingConn->local.port(port);
 
-        if (!Ip::EnableIpv6 && !icpOutgoingConn->local.SetIPv4()) {
+        if (!Ip::EnableIpv6 && !icpOutgoingConn->local.setIPv4()) {
             debugs(49, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << icpOutgoingConn->local << " is not an IPv4 address.");
             fatal("ICP port cannot be opened.");
         }
         /* split-stack for now requires default IPv4-only ICP */
-        if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && icpOutgoingConn->local.IsAnyAddr()) {
-            icpOutgoingConn->local.SetIPv4();
+        if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && icpOutgoingConn->local.isAnyAddr()) {
+            icpOutgoingConn->local.setIPv4();
         }
 
         enter_suid();
         comm_open_listener(SOCK_DGRAM, IPPROTO_UDP, icpOutgoingConn, "Outgoing ICP Port");
         leave_suid();
 
