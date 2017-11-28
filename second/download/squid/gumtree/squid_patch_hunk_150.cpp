     if (vc->busy)
         return;
 
     if (vc->queue->contentSize() == 0)
         return;
 
+    // if retrying after a TC UDP response, our close handler cb may be pending
+    if (fd_table[vc->conn->fd].closing())
+        return;
+
     MemBuf *mb = vc->queue;
 
     vc->queue = new MemBuf;
 
     vc->busy = 1;
 
-    commSetTimeout(vc->fd, Config.Timeout.idns_query, NULL, NULL);
-
-    comm_write_mbuf(vc->fd, mb, idnsSentQueryVC, vc);
+    // Comm needs seconds but idnsCheckQueue() will check the exact timeout
+    const int timeout = (Config.Timeout.idns_query % 1000 ?
+                         Config.Timeout.idns_query + 1000 : Config.Timeout.idns_query) / 1000;
+    AsyncCall::Pointer nil;
+
+    commSetConnTimeout(vc->conn, timeout, nil);
+
+    AsyncCall::Pointer call = commCbCall(78, 5, "idnsSentQueryVC",
+                                         CommIoCbPtrFun(&idnsSentQueryVC, vc));
+    Comm::Write(vc->conn, mb, call);
 
     delete mb;
 }
 
 static void
-idnsInitVCConnected(int fd, const DnsLookupDetails &details, comm_err_t status, int xerrno, void *data)
+idnsInitVCConnected(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno, void *data)
 {
     nsvc * vc = (nsvc *)data;
 
-    if (status != COMM_OK) {
+    if (status != COMM_OK || !conn) {
         char buf[MAX_IPSTRLEN] = "";
         if (vc->ns < nns)
             nameservers[vc->ns].S.NtoA(buf,MAX_IPSTRLEN);
-        debugs(78, 1, HERE << "Failed to connect to nameserver " << buf << " using TCP: " << details);
-        comm_close(fd);
+        debugs(78, 1, HERE << "Failed to connect to nameserver " << buf << " using TCP.");
         return;
     }
 
-    comm_read(fd, (char *)&vc->msglen, 2 , idnsReadVCHeader, vc);
+    vc->conn = conn;
+
+    comm_add_close_handler(conn->fd, idnsVCClosed, vc);
+    AsyncCall::Pointer call = commCbCall(5,4, "idnsReadVCHeader",
+                                         CommIoCbPtrFun(idnsReadVCHeader, vc));
+    comm_read(conn, (char *)&vc->msglen, 2, call);
     vc->busy = 0;
     idnsDoSendQueryVC(vc);
 }
 
 static void
-idnsVCClosed(int fd, void *data)
+idnsVCClosed(const CommCloseCbParams &params)
 {
-    nsvc * vc = (nsvc *)data;
+    nsvc * vc = (nsvc *)params.data;
     delete vc->queue;
     delete vc->msg;
-    if (vc->ns < nns) // XXX: idnsShutdown may have freed nameservers[]
+    vc->conn = NULL;
+    if (vc->ns < nns) // XXX: dnsShutdown may have freed nameservers[]
         nameservers[vc->ns].vc = NULL;
     cbdataFree(vc);
 }
 
 static void
 idnsInitVC(int ns)
 {
-    char buf[MAX_IPSTRLEN];
-
     nsvc *vc = cbdataAlloc(nsvc);
     assert(ns < nns);
+    assert(vc->conn == NULL); // MUST be NULL from the construction process!
     nameservers[ns].vc = vc;
     vc->ns = ns;
+    vc->queue = new MemBuf;
+    vc->msg = new MemBuf;
+    vc->busy = 1;
 
-    IpAddress addr;
+    Comm::ConnectionPointer conn = new Comm::Connection();
 
     if (!Config.Addrs.udp_outgoing.IsNoAddr())
-        addr = Config.Addrs.udp_outgoing;
+        conn->local = Config.Addrs.udp_outgoing;
     else
-        addr = Config.Addrs.udp_incoming;
+        conn->local = Config.Addrs.udp_incoming;
 
-    if (nameservers[ns].S.IsIPv4() && !addr.SetIPv4()) {
-        debugs(31, DBG_CRITICAL, "ERROR: Cannot contact DNS nameserver " << nameservers[ns].S << " from " << addr);
-        addr.SetAnyAddr();
-        addr.SetIPv4();
-    }
+    conn->remote = nameservers[ns].S;
 
-    vc->queue = new MemBuf;
-
-    vc->msg = new MemBuf;
-
-    vc->fd = comm_open(SOCK_STREAM,
-                       IPPROTO_TCP,
-                       addr,
-                       COMM_NONBLOCKING,
-                       "DNS TCP Socket");
-
-    if (vc->fd < 0)
-        fatal("Could not create a DNS socket");
-
-    comm_add_close_handler(vc->fd, idnsVCClosed, vc);
+    if (conn->remote.IsIPv4()) {
+        conn->local.SetIPv4();
+    }
 
-    vc->busy = 1;
+    AsyncCall::Pointer call = commCbCall(78,3, "idnsInitVCConnected", CommConnectCbPtrFun(idnsInitVCConnected, vc));
 
-    commConnectStart(vc->fd, nameservers[ns].S.NtoA(buf,MAX_IPSTRLEN), nameservers[ns].S.GetPort(), idnsInitVCConnected, vc);
+    Comm::ConnOpener *cs = new Comm::ConnOpener(conn, call, Config.Timeout.connect);
+    cs->setHost("DNS TCP Socket");
+    AsyncJob::Start(cs);
 }
 
 static void
 idnsSendQueryVC(idns_query * q, int ns)
 {
     assert(ns < nns);
