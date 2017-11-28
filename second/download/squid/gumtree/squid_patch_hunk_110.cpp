     sslHostName = host;
 
     //HTTPMSGLOCK(currentobject->http->request);
     assert(areAllContextsForThisConnection());
     freeAllContexts();
     //currentobject->connIsFinished();
+
     // We are going to read new request
-    flags.readMoreRequests = true;
-    debugs(33, 5, HERE << "converting FD " << fd << " to SSL");
+    flags.readMore = true;
+    debugs(33, 5, HERE << "converting " << clientConnection << " to SSL");
 
     return getSslContextStart();
 }
 
 #endif /* USE_SSL */
 
+/// check FD after clientHttp[s]ConnectionOpened, adjust HttpSockets as needed
+static bool
+OpenedHttpSocket(const Comm::ConnectionPointer &c, const Ipc::FdNoteId portType)
+{
+    if (!Comm::IsConnOpen(c)) {
+        Must(NHttpSockets > 0); // we tried to open some
+        --NHttpSockets; // there will be fewer sockets than planned
+        Must(HttpSockets[NHttpSockets] < 0); // no extra fds received
+
+        if (!NHttpSockets) // we could not open any listen sockets at all
+            fatalf("Unable to open %s",FdNote(portType));
+
+        return false;
+    }
+    return true;
+}
+
+/// find any unused HttpSockets[] slot and store fd there or return false
+static bool
+AddOpenedHttpSocket(const Comm::ConnectionPointer &conn)
+{
+    bool found = false;
+    for (int i = 0; i < NHttpSockets && !found; ++i) {
+        if ((found = HttpSockets[i] < 0))
+            HttpSockets[i] = conn->fd;
+    }
+    return found;
+}
 
 static void
 clientHttpConnectionsOpen(void)
 {
-    http_port_list *s = NULL;
-    int fd = -1;
-#if USE_SSL
-    int bumpCount = 0; // counts http_ports with sslBump option
-#endif
+    AnyP::PortCfg *s = NULL;
 
     for (s = Config.Sockaddr.http; s; s = s->next) {
-        if (MAXHTTPPORTS == NHttpSockets) {
+        if (MAXTCPLISTENPORTS == NHttpSockets) {
             debugs(1, 1, "WARNING: You have too many 'http_port' lines.");
-            debugs(1, 1, "         The limit is " << MAXHTTPPORTS);
+            debugs(1, 1, "         The limit is " << MAXTCPLISTENPORTS << " HTTP ports.");
             continue;
         }
 
 #if USE_SSL
-        if (s->sslBump &&
-                !s->staticSslContext && !s->generateHostCertificates) {
-            debugs(1, 1, "Will not bump SSL at http_port " <<
-                   s->http.s << " due to SSL initialization failure.");
+        if (s->sslBump && !Config.accessList.ssl_bump) {
+            debugs(33, DBG_IMPORTANT, "WARNING: No ssl_bump configured. Disabling ssl-bump on " << s->protocol << "_port " << s->s);
+            s->sslBump = 0;
+        }
+
+        if (s->sslBump && !s->staticSslContext && !s->generateHostCertificates) {
+            debugs(1, DBG_IMPORTANT, "Will not bump SSL at http_port " << s->s << " due to SSL initialization failure.");
             s->sslBump = 0;
         }
         if (s->sslBump) {
-            ++bumpCount;
             // Create ssl_ctx cache for this port.
             Ssl::TheGlobalContextStorage.addLocalStorage(s->s, s->dynamicCertMemCacheSize == std::numeric_limits<size_t>::max() ? 4194304 : s->dynamicCertMemCacheSize);
         }
 #endif
-#if USE_SSL_CRTD
-        Ssl::Helper::GetInstance();
-#endif //USE_SSL_CRTD
-
-        enter_suid();
-
-        if (s->spoof_client_ip) {
-            fd = comm_open_listener(SOCK_STREAM, IPPROTO_TCP, s->s, (COMM_NONBLOCKING|COMM_TRANSPARENT), "HTTP Socket");
-        } else {
-            fd = comm_open_listener(SOCK_STREAM, IPPROTO_TCP, s->s, COMM_NONBLOCKING, "HTTP Socket");
-        }
-
-        leave_suid();
 
-        if (fd < 0)
-            continue;
-
-        comm_listen(fd);
-
-        comm_accept(fd, httpAccept, s);
-
-        debugs(1, 1, "Accepting " <<
-               (s->intercepted ? " intercepted" : "") <<
-               (s->spoof_client_ip ? " spoofing" : "") <<
-               (s->sslBump ? " bumpy" : "") <<
-               (s->accel ? " accelerated" : "")
-               << " HTTP connections at " << s->s
-               << ", FD " << fd << "." );
+        // Fill out a Comm::Connection which IPC will open as a listener for us
+        //  then pass back when active so we can start a TcpAcceptor subscription.
+        s->listenConn = new Comm::Connection;
+        s->listenConn->local = s->s;
+        s->listenConn->flags = COMM_NONBLOCKING | (s->spoof_client_ip ? COMM_TRANSPARENT : 0) | (s->intercepted ? COMM_INTERCEPTION : 0);
+
+        // setup the subscriptions such that new connections accepted by listenConn are handled by HTTP
+        typedef CommCbFunPtrCallT<CommAcceptCbPtrFun> AcceptCall;
+        RefCount<AcceptCall> subCall = commCbCall(5, 5, "httpAccept", CommAcceptCbPtrFun(httpAccept, s));
+        Subscription::Pointer sub = new CallSubscription<AcceptCall>(subCall);
+
+        AsyncCall::Pointer listenCall = asyncCall(33,2, "clientListenerConnectionOpened",
+                                        ListeningStartedDialer(&clientListenerConnectionOpened, s, Ipc::fdnHttpSocket, sub));
+        Ipc::StartListening(SOCK_STREAM, IPPROTO_TCP, s->listenConn, Ipc::fdnHttpSocket, listenCall);
 
-        HttpSockets[NHttpSockets++] = fd;
+        HttpSockets[NHttpSockets] = -1; // set in clientListenerConnectionOpened
+        ++NHttpSockets;
     }
-
-#if USE_SSL
-    if (bumpCount && !Config.accessList.ssl_bump)
-        debugs(33, 1, "WARNING: http_port(s) with SslBump found, but no " <<
-               std::endl << "\tssl_bump ACL configured. No requests will be " <<
-               "bumped.");
-#endif
 }
 
 #if USE_SSL
 static void
 clientHttpsConnectionsOpen(void)
 {
-    https_port_list *s;
-    int fd;
+    AnyP::PortCfg *s;
 
-    for (s = Config.Sockaddr.https; s; s = (https_port_list *)s->http.next) {
-        if (MAXHTTPPORTS == NHttpSockets) {
+    for (s = Config.Sockaddr.https; s; s = s->next) {
+        if (MAXTCPLISTENPORTS == NHttpSockets) {
             debugs(1, 1, "Ignoring 'https_port' lines exceeding the limit.");
-            debugs(1, 1, "The limit is " << MAXHTTPPORTS << " HTTPS ports.");
+            debugs(1, 1, "The limit is " << MAXTCPLISTENPORTS << " HTTPS ports.");
             continue;
         }
 
         if (!s->staticSslContext) {
-            debugs(1, 1, "Ignoring https_port " << s->http.s <<
+            debugs(1, 1, "Ignoring https_port " << s->s <<
                    " due to SSL initialization failure.");
             continue;
         }
 
-        enter_suid();
-        fd = comm_open_listener(SOCK_STREAM,
-                                IPPROTO_TCP,
-                                s->http.s,
-                                COMM_NONBLOCKING, "HTTPS Socket");
-        leave_suid();
+        // Fill out a Comm::Connection which IPC will open as a listener for us
+        s->listenConn = new Comm::Connection;
+        s->listenConn->local = s->s;
+        s->listenConn->flags = COMM_NONBLOCKING | (s->spoof_client_ip ? COMM_TRANSPARENT : 0) |
+                               (s->intercepted ? COMM_INTERCEPTION : 0);
 
-        if (fd < 0)
-            continue;
+        // setup the subscriptions such that new connections accepted by listenConn are handled by HTTPS
+        typedef CommCbFunPtrCallT<CommAcceptCbPtrFun> AcceptCall;
+        RefCount<AcceptCall> subCall = commCbCall(5, 5, "httpsAccept", CommAcceptCbPtrFun(httpsAccept, s));
+        Subscription::Pointer sub = new CallSubscription<AcceptCall>(subCall);
 
-        comm_listen(fd);
+        AsyncCall::Pointer listenCall = asyncCall(33, 2, "clientListenerConnectionOpened",
+                                        ListeningStartedDialer(&clientListenerConnectionOpened,
+                                                               s, Ipc::fdnHttpsSocket, sub));
+        Ipc::StartListening(SOCK_STREAM, IPPROTO_TCP, s->listenConn, Ipc::fdnHttpsSocket, listenCall);
+        HttpSockets[NHttpSockets] = -1;
+        ++NHttpSockets;
+    }
+}
+#endif
 
-        comm_accept(fd, httpsAccept, s);
+/// process clientHttpConnectionsOpen result
+static void
+clientListenerConnectionOpened(AnyP::PortCfg *s, const Ipc::FdNoteId portTypeNote, const Subscription::Pointer &sub)
+{
+    if (!OpenedHttpSocket(s->listenConn, portTypeNote))
+        return;
 
-        debugs(1, 1, "Accepting HTTPS connections at " << s->http.s << ", FD " << fd << ".");
+    Must(s);
+    Must(Comm::IsConnOpen(s->listenConn));
 
-        HttpSockets[NHttpSockets++] = fd;
-    }
-}
+    // TCP: setup a job to handle accept() with subscribed handler
+    AsyncJob::Start(new Comm::TcpAcceptor(s->listenConn, FdNote(portTypeNote), sub));
 
-#endif
+    debugs(1, 1, "Accepting " <<
+           (s->intercepted ? "NAT intercepted " : "") <<
+           (s->spoof_client_ip ? "TPROXY spoofing " : "") <<
+           (s->sslBump ? "SSL bumped " : "") <<
+           (s->accel ? "reverse-proxy " : "")
+           << FdNote(portTypeNote) << " connections at "
+           << s->listenConn);
+
+    Must(AddOpenedHttpSocket(s->listenConn)); // otherwise, we have received a fd we did not ask for
+}
 
 void
 clientOpenListenSockets(void)
 {
     clientHttpConnectionsOpen();
 #if USE_SSL
