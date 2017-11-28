         rcode = 0;
     else if (rcode < 0)
         rcode = -rcode;
 
     if (rcode < MAX_RCODE)
         if (attempt < MAX_ATTEMPT)
-            RcodeMatrix[rcode][attempt]++;
+            ++ RcodeMatrix[rcode][attempt];
 }
 
 /* ====================================================================== */
 
 static void
 idnsRegisterWithCacheManager(void)
 {
-    CacheManager::GetInstance()->
-    registerAction("idns", "Internal DNS Statistics", idnsStats, 0, 1);
+    Mgr::RegisterAction("idns", "Internal DNS Statistics", idnsStats, 0, 1);
 }
 
 void
-idnsInit(void)
+dnsInit(void)
 {
     static int init = 0;
 
     CBDATA_INIT_TYPE(nsvc);
     CBDATA_INIT_TYPE(idns_query);
 
     if (DnsSocketA < 0 && DnsSocketB < 0) {
-        IpAddress addrA; // since we don't want to alter Config.Addrs.udp_* and dont have one of our own.
+        Ip::Address addrV6; // since we don't want to alter Config.Addrs.udp_* and dont have one of our own.
 
         if (!Config.Addrs.udp_outgoing.IsNoAddr())
-            addrA = Config.Addrs.udp_outgoing;
+            addrV6 = Config.Addrs.udp_outgoing;
         else
-            addrA = Config.Addrs.udp_incoming;
+            addrV6 = Config.Addrs.udp_incoming;
 
-        IpAddress addrB = addrA;
-        addrA.SetIPv4();
+        Ip::Address addrV4 = addrV6;
+        addrV4.SetIPv4();
 
-        if (Ip::EnableIpv6 && addrB.IsIPv6()) {
-            debugs(78, 2, "idnsInit: attempt open DNS socket to: " << addrB);
+        if (Ip::EnableIpv6 && addrV6.IsIPv6()) {
+            debugs(78, 2, "idnsInit: attempt open DNS socket to: " << addrV6);
             DnsSocketB = comm_open_listener(SOCK_DGRAM,
                                             IPPROTO_UDP,
-                                            addrB,
+                                            addrV6,
                                             COMM_NONBLOCKING,
                                             "DNS Socket IPv6");
         }
 
-        if (addrA.IsIPv4()) {
-            debugs(78, 2, "idnsInit: attempt open DNS socket to: " << addrA);
+        if (addrV4.IsIPv4()) {
+            debugs(78, 2, "idnsInit: attempt open DNS socket to: " << addrV4);
             DnsSocketA = comm_open_listener(SOCK_DGRAM,
                                             IPPROTO_UDP,
-                                            addrA,
+                                            addrV4,
                                             COMM_NONBLOCKING,
                                             "DNS Socket IPv4");
         }
 
         if (DnsSocketA < 0 && DnsSocketB < 0)
             fatal("Could not create a DNS socket");
 
         /* Ouch... we can't call functions using debug from a debug
          * statement. Doing so messes up the internal Debug::level
          */
         if (DnsSocketB >= 0) {
             comm_local_port(DnsSocketB);
-            debugs(78, 1, "DNS Socket created at " << addrB << ", FD " << DnsSocketB);
-            commSetSelect(DnsSocketB, COMM_SELECT_READ, idnsRead, NULL, 0);
+            debugs(78, 1, "DNS Socket created at " << addrV6 << ", FD " << DnsSocketB);
+            Comm::SetSelect(DnsSocketB, COMM_SELECT_READ, idnsRead, NULL, 0);
         }
         if (DnsSocketA >= 0) {
             comm_local_port(DnsSocketA);
-            debugs(78, 1, "DNS Socket created at " << addrA << ", FD " << DnsSocketA);
-            commSetSelect(DnsSocketA, COMM_SELECT_READ, idnsRead, NULL, 0);
+            debugs(78, 1, "DNS Socket created at " << addrV4 << ", FD " << DnsSocketA);
+            Comm::SetSelect(DnsSocketA, COMM_SELECT_READ, idnsRead, NULL, 0);
         }
     }
 
     assert(0 == nns);
     idnsParseNameservers();
-#ifndef _SQUID_MSWIN_
+#if !_SQUID_MSWIN_
 
     if (0 == nns)
         idnsParseResolvConf();
 
 #endif
-#ifdef _SQUID_WIN32_
-
+#if _SQUID_WINDOWS_
     if (0 == nns)
         idnsParseWIN32Registry();
-
 #endif
 
     if (0 == nns) {
         debugs(78, 1, "Warning: Could not find any nameservers. Trying to use localhost");
-#ifdef _SQUID_WIN32_
-
+#if _SQUID_WINDOWS_
         debugs(78, 1, "Please check your TCP-IP settings or /etc/resolv.conf file");
 #else
-
         debugs(78, 1, "Please check your /etc/resolv.conf file");
 #endif
 
         debugs(78, 1, "or use the 'dns_nameservers' option in squid.conf.");
         idnsAddNameserver("127.0.0.1");
     }
