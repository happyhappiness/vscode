 
         if (peer->sslSession)
             SSL_set_session(ssl, peer->sslSession);
 
     } else {
         SSL_set_ex_data(ssl, ssl_ex_index_server, (void*)request->GetHost());
+
+        // We need to set SNI TLS extension only in the case we are
+        // connecting direct to origin server
+        Ssl::setClientSNI(ssl, request->GetHost());
     }
 
     // Create the ACL check list now, while we have access to more info.
     // The list is used in ssl_verify_cb() and is freed in ssl_free().
     if (acl_access *acl = Config.ssl_client.cert_error) {
         ACLFilledChecklist *check = new ACLFilledChecklist(acl, request, dash_str);
-        check->fd(fd);
         SSL_set_ex_data(ssl, ssl_ex_index_cert_error_check, check);
     }
 
     fd_table[fd].ssl = ssl;
     fd_table[fd].read_method = &ssl_read_method;
     fd_table[fd].write_method = &ssl_write_method;
     negotiateSSL(fd);
 }
 
 #endif
 
 void
-FwdState::connectDone(int aServerFD, const DnsLookupDetails &dns, comm_err_t status, int xerrno)
+FwdState::connectDone(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno)
 {
-    FwdServer *fs = servers;
-    assert(server_fd == aServerFD);
-
-    request->recordLookup(dns);
-
-    if (Config.onoff.log_ip_on_direct && status != COMM_ERR_DNS && fs->code == HIER_DIRECT)
-        updateHierarchyInfo();
-
-    if (status == COMM_ERR_DNS) {
-        /*
-         * Only set the dont_retry flag if the DNS lookup fails on
-         * a direct connection.  If DNS lookup fails when trying
-         * a neighbor cache, we may want to retry another option.
-         */
-
-        if (NULL == fs->_peer)
-            flags.dont_retry = 1;
-
-        debugs(17, 4, "fwdConnectDone: Unknown host: " << request->GetHost());
-
-        ErrorState *const anErr = makeConnectingError(ERR_DNS_FAIL);
-
-        anErr->dnsError = dns.error;
-
-        fail(anErr);
-
-        comm_close(server_fd);
-    } else if (status != COMM_OK) {
-        assert(fs);
+    if (status != COMM_OK) {
         ErrorState *const anErr = makeConnectingError(ERR_CONNECT_FAIL);
         anErr->xerrno = xerrno;
-
         fail(anErr);
 
-        if (fs->_peer)
-            peerConnectFailed(fs->_peer);
+        /* it might have been a timeout with a partially open link */
+        if (conn != NULL) {
+            if (conn->getPeer())
+                peerConnectFailed(conn->getPeer());
 
-        comm_close(server_fd);
-    } else {
-        debugs(17, 3, "fwdConnectDone: FD " << server_fd << ": '" << entry->url() << "'" );
+            conn->close();
+        }
+        retryOrBail();
+        return;
+    }
 
-        if (fs->_peer)
-            peerConnectSucceded(fs->_peer);
+    serverConn = conn;
+    flags.connected_okay = true;
 
-#if USE_SSL
+    debugs(17, 3, HERE << serverConnection() << ": '" << entry->url() << "'" );
 
-        if ((fs->_peer && fs->_peer->use_ssl) ||
-                (!fs->_peer && request->protocol == PROTO_HTTPS)) {
-            if (fs->code != PINNED) {
-                initiateSSL();
-                return;
-            }
-        }
+    comm_add_close_handler(serverConnection()->fd, fwdServerClosedWrapper, this);
 
-#endif
-        dispatch();
+    if (serverConnection()->getPeer())
+        peerConnectSucceded(serverConnection()->getPeer());
+
+#if USE_SSL
+    if (!request->flags.pinned) {
+        if ((serverConnection()->getPeer() && serverConnection()->getPeer()->use_ssl) ||
+                (!serverConnection()->getPeer() && request->protocol == AnyP::PROTO_HTTPS)) {
+            initiateSSL();
+            return;
+        }
     }
+#endif
+
+    dispatch();
 }
 
 void
 FwdState::connectTimeout(int fd)
 {
-    FwdServer *fs = servers;
-
     debugs(17, 2, "fwdConnectTimeout: FD " << fd << ": '" << entry->url() << "'" );
-    assert(fd == server_fd);
-
-    if (Config.onoff.log_ip_on_direct && fs->code == HIER_DIRECT && fd_table[fd].ipaddr[0])
-        updateHierarchyInfo();
+    assert(serverDestinations[0] != NULL);
+    assert(fd == serverDestinations[0]->fd);
 
     if (entry->isEmpty()) {
-        ErrorState *anErr = errorCon(ERR_CONNECT_FAIL, HTTP_GATEWAY_TIMEOUT, request);
+        ErrorState *anErr = new ErrorState(ERR_CONNECT_FAIL, HTTP_GATEWAY_TIMEOUT, request);
         anErr->xerrno = ETIMEDOUT;
         fail(anErr);
-        /*
-         * This marks the peer DOWN ...
-         */
 
-        if (servers)
-            if (servers->_peer)
-                peerConnectFailed(servers->_peer);
+        /* This marks the peer DOWN ... */
+        if (serverDestinations[0]->getPeer())
+            peerConnectFailed(serverDestinations[0]->getPeer());
     }
 
-    comm_close(fd);
+    if (Comm::IsConnOpen(serverDestinations[0])) {
+        serverDestinations[0]->close();
+    }
 }
 
+/**
+ * Called after Forwarding path selection (via peer select) has taken place.
+ * And whenever forwarding needs to attempt a new connection (routing failover)
+ * We have a vector of possible localIP->remoteIP paths now ready to start being connected.
+ */
 void
 FwdState::connectStart()
 {
-    const char *url = entry->url();
-    int fd = -1;
-    FwdServer *fs = servers;
-    const char *host;
-    unsigned short port;
-    int ctimeout;
-    int ftimeout = Config.Timeout.forward - (squid_curtime - start_t);
+    assert(serverDestinations.size() > 0);
 
-    IpAddress outgoing;
-    unsigned short tos;
-    IpAddress client_addr;
-    assert(fs);
-    assert(server_fd == -1);
-    debugs(17, 3, "fwdConnectStart: " << url);
+    debugs(17, 3, "fwdConnectStart: " << entry->url());
 
     if (n_tries == 0) // first attempt
         request->hier.first_conn_start = current_time;
 
-    if (fs->_peer) {
-        ctimeout = fs->_peer->connect_timeout > 0 ? fs->_peer->connect_timeout
-                   : Config.Timeout.peer_connect;
+    /* connection timeout */
+    int ctimeout;
+    if (serverDestinations[0]->getPeer()) {
+        ctimeout = serverDestinations[0]->getPeer()->connect_timeout > 0 ?
+                   serverDestinations[0]->getPeer()->connect_timeout : Config.Timeout.peer_connect;
     } else {
         ctimeout = Config.Timeout.connect;
     }
 
-    if (request->flags.spoof_client_ip) {
-        if (!fs->_peer || !fs->_peer->options.no_tproxy)
-            client_addr = request->client_addr;
-        // else no tproxy today ...
-    }
-
+    /* calculate total forwarding timeout ??? */
+    int ftimeout = Config.Timeout.forward - (squid_curtime - start_t);
     if (ftimeout < 0)
         ftimeout = 5;
 
     if (ftimeout < ctimeout)
         ctimeout = ftimeout;
 
-    if (fs->_peer && request->flags.sslBumped == true) {
+    if (serverDestinations[0]->getPeer() && request->flags.sslBumped == true) {
         debugs(50, 4, "fwdConnectStart: Ssl bumped connections through parrent proxy are not allowed");
-        ErrorState *anErr = errorCon(ERR_CANNOT_FORWARD, HTTP_SERVICE_UNAVAILABLE, request);
+        ErrorState *anErr = new ErrorState(ERR_CANNOT_FORWARD, HTTP_SERVICE_UNAVAILABLE, request);
         fail(anErr);
         self = NULL; // refcounted
         return;
     }
 
-    request->flags.pinned = 0;
-    if (fs->code == PINNED) {
+    request->flags.pinned = 0; // XXX: what if the ConnStateData set this to flag existing credentials?
+    // XXX: answer: the peer selection *should* catch it and give us only the pinned peer. so we reverse the =0 step below.
+    // XXX: also, logs will now lie if pinning is broken and leads to an error message.
+    if (serverDestinations[0]->peerType == PINNED) {
         ConnStateData *pinned_connection = request->pinnedConnection();
-        assert(pinned_connection);
-        fd = pinned_connection->validatePinnedConnection(request, fs->_peer);
-        if (fd >= 0) {
-            pinned_connection->unpinConnection();
+        // pinned_connection may become nil after a pconn race
+        if (pinned_connection)
+            serverConn = pinned_connection->validatePinnedConnection(request, serverDestinations[0]->getPeer());
+        else
+            serverConn = NULL;
+        if (Comm::IsConnOpen(serverConn)) {
+            flags.connected_okay = true;
 #if 0
-            if (!fs->_peer)
-                fs->code = HIER_DIRECT;
+            if (!serverConn->getPeer())
+                serverConn->peerType = HIER_DIRECT;
 #endif
-            server_fd = fd;
-            n_tries++;
+            ++n_tries;
             request->flags.pinned = 1;
             if (pinned_connection->pinnedAuth())
                 request->flags.auth = 1;
-            comm_add_close_handler(fd, fwdServerClosedWrapper, this);
-            updateHierarchyInfo();
-            connectDone(fd, DnsLookupDetails(), COMM_OK, 0);
+            // the server may close the pinned connection before this request
+            pconnRace = racePossible;
+            dispatch();
             return;
         }
         /* Failure. Fall back on next path */
-        debugs(17,2,HERE << " Pinned connection " << pinned_connection << " not valid. Releasing.");
-        request->releasePinnedConnection();
-        servers = fs->next;
-        fwdServerFree(fs);
-        connectStart();
+        debugs(17,2,HERE << " Pinned connection " << pinned_connection << " not valid.");
+        serverDestinations.shift();
+        startConnectionOrFail();
         return;
     }
 
-    if (fs->_peer) {
-        host = fs->_peer->host;
-        port = fs->_peer->http_port;
-        fd = fwdPconnPool->pop(fs->_peer->name, fs->_peer->http_port, request->GetHost(), client_addr, checkRetriable());
-    } else {
+    // Use pconn to avoid opening a new connection.
+    const char *host = NULL;
+    if (!serverDestinations[0]->getPeer())
         host = request->GetHost();
-        port = request->port;
-        fd = fwdPconnPool->pop(host, port, NULL, client_addr, checkRetriable());
-    }
-    if (fd >= 0) {
-        debugs(17, 3, "fwdConnectStart: reusing pconn FD " << fd);
-        server_fd = fd;
-        n_tries++;
-
-        if (!fs->_peer)
-            origin_tries++;
-
-        updateHierarchyInfo();
-
-        comm_add_close_handler(fd, fwdServerClosedWrapper, this);
 
-        if (comm_local_port(fd))
-            request->hier.peer_local_addr = fd_table[fd].local_addr;
+    Comm::ConnectionPointer temp;
+    // Avoid pconns after races so that the same client does not suffer twice.
+    // This does not increase the total number of connections because we just
+    // closed the connection that failed the race. And re-pinning assumes this.
+    if (pconnRace != raceHappened)
+        temp = fwdPconnPool->pop(serverDestinations[0], host, checkRetriable());
+
+    const bool openedPconn = Comm::IsConnOpen(temp);
+    pconnRace = openedPconn ? racePossible : raceImpossible;
+
+    // if we found an open persistent connection to use. use it.
+    if (openedPconn) {
+        serverConn = temp;
+        flags.connected_okay = true;
+        debugs(17, 3, HERE << "reusing pconn " << serverConnection());
+        ++n_tries;
+
+        comm_add_close_handler(serverConnection()->fd, fwdServerClosedWrapper, this);
+
+        /* Update server side TOS and Netfilter mark on the connection. */
+        if (Ip::Qos::TheConfig.isAclTosActive()) {
+            temp->tos = GetTosToServer(request);
+            Ip::Qos::setSockTos(temp, temp->tos);
+        }
+#if SO_MARK
+        if (Ip::Qos::TheConfig.isAclNfmarkActive()) {
+            temp->nfmark = GetNfmarkToServer(request);
+            Ip::Qos::setSockNfmark(temp, temp->nfmark);
+        }
+#endif
 
         dispatch();
-
         return;
     }
 
+    // We will try to open a new connection, possibly to the same destination.
+    // We reset serverDestinations[0] in case we are using it again because
+    // ConnOpener modifies its destination argument.
+    serverDestinations[0]->local.SetPort(0);
+    serverConn = NULL;
+
 #if URL_CHECKSUM_DEBUG
     entry->mem_obj->checkUrlChecksum();
 #endif
 
-    outgoing = getOutgoingAddr(request, fs->_peer);
-
-    // if IPv6 is disabled try to force IPv4-only outgoing.
-    if (!Ip::EnableIpv6 && !outgoing.SetIPv4()) {
-        debugs(50, 4, "fwdConnectStart: IPv6 is Disabled. Cannot connect from " << outgoing);
-        ErrorState *anErr = errorCon(ERR_CONNECT_FAIL, HTTP_SERVICE_UNAVAILABLE, request);
-        anErr->xerrno = EAFNOSUPPORT;
-        fail(anErr);
-        self = NULL;	// refcounted
-        return;
-    }
-
-    // if IPv6 is split-stack, prefer IPv4
-    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK) {
-        // NP: This is not a great choice of default,
-        // but with the current Internet being IPv4-majority has a higher success rate.
-        // if setting to IPv4 fails we dont care, that just means to use IPv6 outgoing.
-        outgoing.SetIPv4();
-    }
-
-    tos = getOutgoingTOS(request);
-
-    debugs(17, 3, "fwdConnectStart: got outgoing addr " << outgoing << ", tos " << tos);
-
-    int commFlags = COMM_NONBLOCKING;
-    if (request->flags.spoof_client_ip) {
-        if (!fs->_peer || !fs->_peer->options.no_tproxy)
-            commFlags |= COMM_TRANSPARENT;
-        // else no tproxy today ...
-    }
-
-    fd = comm_openex(SOCK_STREAM, IPPROTO_TCP, outgoing, commFlags, tos, url);
-
-    debugs(17, 3, "fwdConnectStart: got TCP FD " << fd);
-
-    if (fd < 0) {
-        debugs(50, 4, "fwdConnectStart: " << xstrerror());
-        ErrorState *anErr = errorCon(ERR_SOCKET_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
-        anErr->xerrno = errno;
-        fail(anErr);
-        self = NULL;	// refcounted
-        return;
-    }
-
-    server_fd = fd;
-    n_tries++;
-
-    if (!fs->_peer)
-        origin_tries++;
-
-    if (comm_local_port(fd))
-        request->hier.peer_local_addr = fd_table[fd].local_addr;
-
-    /*
-     * stats.conn_open is used to account for the number of
-     * connections that we have open to the peer, so we can limit
-     * based on the max-conn option.  We need to increment here,
-     * even if the connection may fail.
-     */
-
-    if (fs->_peer) {
-        fs->_peer->stats.conn_open++;
-        comm_add_close_handler(fd, fwdPeerClosed, fs->_peer);
-    }
-
-    comm_add_close_handler(fd, fwdServerClosedWrapper, this);
-
-    commSetTimeout(fd, ctimeout, fwdConnectTimeoutWrapper, this);
-
-#if LINUX_TPROXY2
-    if (!fs->_peer && request->flags.spoof_client_ip) {
-        // try to set the outgoing address using TPROXY v2
-        // if it fails we abort any further TPROXY actions on this connection
-        if (IpInterceptor.SetTproxy2OutgoingAddr(fd, src) == -1) {
-            request->flags.spoof_client_ip = 0;
-        }
-    }
+    /* Get the server side TOS and Netfilter mark to be set on the connection. */
+    if (Ip::Qos::TheConfig.isAclTosActive()) {
+        serverDestinations[0]->tos = GetTosToServer(request);
+    }
+#if SO_MARK && USE_LIBCAP
+    serverDestinations[0]->nfmark = GetNfmarkToServer(request);
+    debugs(17, 3, "fwdConnectStart: got outgoing addr " << serverDestinations[0]->local << ", tos " << int(serverDestinations[0]->tos)
+           << ", netfilter mark " << serverDestinations[0]->nfmark);
+#else
+    serverDestinations[0]->nfmark = 0;
+    debugs(17, 3, "fwdConnectStart: got outgoing addr " << serverDestinations[0]->local << ", tos " << int(serverDestinations[0]->tos));
 #endif
 
-    updateHierarchyInfo();
-    commConnectStart(fd, host, port, fwdConnectDoneWrapper, this);
-}
-
-void
-FwdState::startComplete(FwdServer * theServers)
-{
-    debugs(17, 3, "fwdStartComplete: " << entry->url()  );
-
-    if (theServers != NULL) {
-        servers = theServers;
-        connectStart();
-    } else {
-        startFail();
-    }
-}
-
-void
-FwdState::startFail()
-{
-    debugs(17, 3, "fwdStartFail: " << entry->url()  );
-    ErrorState *anErr = errorCon(ERR_CANNOT_FORWARD, HTTP_SERVICE_UNAVAILABLE, request);
-    anErr->xerrno = errno;
-    fail(anErr);
-    self = NULL;	// refcounted
+    calls.connector = commCbCall(17,3, "fwdConnectDoneWrapper", CommConnectCbPtrFun(fwdConnectDoneWrapper, this));
+    Comm::ConnOpener *cs = new Comm::ConnOpener(serverDestinations[0], calls.connector, ctimeout);
+    if (host)
+        cs->setHost(host);
+    AsyncJob::Start(cs);
 }
 
 void
 FwdState::dispatch()
 {
-    peer *p = NULL;
-    debugs(17, 3, "fwdDispatch: FD " << client_fd << ": Fetching '" << RequestMethodStr(request->method) << " " << entry->url() << "'" );
+    debugs(17, 3, HERE << clientConn << ": Fetching '" << RequestMethodStr(request->method) << " " << entry->url() << "'");
     /*
      * Assert that server_fd is set.  This is to guarantee that fwdState
      * is attached to something and will be deallocated when server_fd
      * is closed.
      */
-    assert(server_fd > -1);
+    assert(Comm::IsConnOpen(serverConn));
 
-    fd_note(server_fd, entry->url());
+    fd_note(serverConnection()->fd, entry->url());
 
-    fd_table[server_fd].noteUse(fwdPconnPool);
+    fd_table[serverConnection()->fd].noteUse(fwdPconnPool);
 
     /*assert(!EBIT_TEST(entry->flags, ENTRY_DISPATCHED)); */
     assert(entry->ping_status != PING_WAITING);
 
     assert(entry->lock_count);
 
     EBIT_SET(entry->flags, ENTRY_DISPATCHED);
 
     netdbPingSite(request->GetHost());
 
-#if USE_ZPH_QOS && defined(_SQUID_LINUX_)
-    /* Bug 2537: This part of ZPH only applies to patched Linux kernels. */
-
-    /* Retrieves remote server TOS value, and stores it as part of the
+    /* Retrieves remote server TOS or MARK value, and stores it as part of the
      * original client request FD object. It is later used to forward
-     * remote server's TOS in the response to the client in case of a MISS.
+     * remote server's TOS/MARK in the response to the client in case of a MISS.
      */
-    fde * clientFde = &fd_table[client_fd];
-    if (clientFde) {
-        int tos = 1;
-        int tos_len = sizeof(tos);
-        clientFde->upstreamTOS = 0;
-        if (setsockopt(server_fd,SOL_IP,IP_RECVTOS,&tos,tos_len)==0) {
-            unsigned char buf[512];
-            int len = 512;
-            if (getsockopt(server_fd,SOL_IP,IP_PKTOPTIONS,buf,(socklen_t*)&len) == 0) {
-                /* Parse the PKTOPTIONS structure to locate the TOS data message
-                 * prepared in the kernel by the ZPH incoming TCP TOS preserving
-                 * patch.
-                 */
-                unsigned char * pbuf = buf;
-                while (pbuf-buf < len) {
-                    struct cmsghdr *o = (struct cmsghdr*)pbuf;
-                    if (o->cmsg_len<=0)
-                        break;
-
-                    if (o->cmsg_level == SOL_IP && o->cmsg_type == IP_TOS) {
-                        int *tmp = (int*)CMSG_DATA(o);
-                        clientFde->upstreamTOS = (unsigned char)*tmp;
-                        break;
-                    }
-                    pbuf += CMSG_LEN(o->cmsg_len);
-                }
-            } else {
-                debugs(33, 1, "ZPH: error in getsockopt(IP_PKTOPTIONS) on FD "<<server_fd<<" "<<xstrerror());
-            }
-        } else {
-            debugs(33, 1, "ZPH: error in setsockopt(IP_RECVTOS) on FD "<<server_fd<<" "<<xstrerror());
+    if (Ip::Qos::TheConfig.isHitNfmarkActive()) {
+        if (Comm::IsConnOpen(clientConn) && Comm::IsConnOpen(serverConnection())) {
+            fde * clientFde = &fd_table[clientConn->fd]; // XXX: move the fd_table access into Ip::Qos
+            /* Get the netfilter mark for the connection */
+            Ip::Qos::getNfmarkFromServer(serverConnection(), clientFde);
+        }
+    }
+
+#if _SQUID_LINUX_
+    /* Bug 2537: The TOS forward part of QOS only applies to patched Linux kernels. */
+    if (Ip::Qos::TheConfig.isHitTosActive()) {
+        if (Comm::IsConnOpen(clientConn)) {
+            fde * clientFde = &fd_table[clientConn->fd]; // XXX: move the fd_table access into Ip::Qos
+            /* Get the TOS value for the packet */
+            Ip::Qos::getTosFromServer(serverConnection(), clientFde);
         }
     }
 #endif
 
-    if (servers && (p = servers->_peer)) {
-        p->stats.fetches++;
-        request->peer_login = p->login;
-        request->peer_domain = p->domain;
+    if (serverConnection()->getPeer() != NULL) {
+        ++ serverConnection()->getPeer()->stats.fetches;
+        request->peer_login = serverConnection()->getPeer()->login;
+        request->peer_domain = serverConnection()->getPeer()->domain;
         httpStart(this);
     } else {
         request->peer_login = NULL;
         request->peer_domain = NULL;
 
         switch (request->protocol) {
 #if USE_SSL
 
-        case PROTO_HTTPS:
+        case AnyP::PROTO_HTTPS:
             httpStart(this);
             break;
 #endif
 
-        case PROTO_HTTP:
+        case AnyP::PROTO_HTTP:
             httpStart(this);
             break;
 
-        case PROTO_GOPHER:
+        case AnyP::PROTO_GOPHER:
             gopherStart(this);
             break;
 
-        case PROTO_FTP:
+        case AnyP::PROTO_FTP:
             ftpStart(this);
             break;
 
-        case PROTO_CACHEOBJ:
+        case AnyP::PROTO_CACHE_OBJECT:
 
-        case PROTO_INTERNAL:
+        case AnyP::PROTO_INTERNAL:
 
-        case PROTO_URN:
+        case AnyP::PROTO_URN:
             fatal_dump("Should never get here");
             break;
 
-        case PROTO_WHOIS:
+        case AnyP::PROTO_WHOIS:
             whoisStart(this);
             break;
 
-        case PROTO_WAIS:	/* Not implemented */
+        case AnyP::PROTO_WAIS:	/* Not implemented */
 
         default:
-            debugs(17, 1, "fwdDispatch: Cannot retrieve '" << entry->url() << "'" );
-            ErrorState *anErr = errorCon(ERR_UNSUP_REQ, HTTP_BAD_REQUEST, request);
+            debugs(17, DBG_IMPORTANT, "WARNING: Cannot retrieve '" << entry->url() << "'.");
+            ErrorState *anErr = new ErrorState(ERR_UNSUP_REQ, HTTP_BAD_REQUEST, request);
             fail(anErr);
-            /*
-             * Force a persistent connection to be closed because
-             * some Netscape browsers have a bug that sends CONNECT
-             * requests as GET's over persistent connections.
-             */
-            request->flags.proxy_keepalive = 0;
-            /*
-             * Set the dont_retry flag becuase this is not a
-             * transient (network) error; its a bug.
-             */
+            // Set the dont_retry flag because this is not a transient (network) error.
             flags.dont_retry = 1;
-            comm_close(server_fd);
+            if (Comm::IsConnOpen(serverConn)) {
+                serverConn->close();
+            }
             break;
         }
     }
 }
 
 /*
  * FwdState::reforward
  *
  * returns TRUE if the transaction SHOULD be re-forwarded to the
- * next choice in the FwdServers list.  This method is called when
+ * next choice in the serverDestinations list.  This method is called when
  * server-side communication completes normally, or experiences
  * some error after receiving the end of HTTP headers.
  */
 int
 FwdState::reforward()
 {
     StoreEntry *e = entry;
-    FwdServer *fs = servers;
     http_status s;
+
+    if (EBIT_TEST(e->flags, ENTRY_ABORTED)) {
+        debugs(17, 3, HERE << "entry aborted");
+        return 0;
+    }
+
     assert(e->store_status == STORE_PENDING);
     assert(e->mem_obj);
 #if URL_CHECKSUM_DEBUG
 
     e->mem_obj->checkUrlChecksum();
 #endif
 
-    debugs(17, 3, "fwdReforward: " << e->url() << "?" );
+    debugs(17, 3, HERE << e->url() << "?" );
 
     if (!EBIT_TEST(e->flags, ENTRY_FWD_HDR_WAIT)) {
-        debugs(17, 3, "fwdReforward: No, ENTRY_FWD_HDR_WAIT isn't set");
+        debugs(17, 3, HERE << "No, ENTRY_FWD_HDR_WAIT isn't set");
         return 0;
     }
 
     if (n_tries > Config.forward_max_tries)
         return 0;
 
-    if (origin_tries > 1)
-        return 0;
-
     if (request->bodyNibbled())
         return 0;
 
-    assert(fs);
-
-    servers = fs->next;
-
-    fwdServerFree(fs);
-
-    if (servers == NULL) {
-        debugs(17, 3, "fwdReforward: No forward-servers left");
+    if (serverDestinations.size() <= 1) {
+        // NP: <= 1 since total count includes the recently failed one.
+        debugs(17, 3, HERE << "No alternative forwarding paths left");
         return 0;
     }
 
     s = e->getReply()->sline.status;
-    debugs(17, 3, "fwdReforward: status " << s);
+    debugs(17, 3, HERE << "status " << s);
     return reforwardableStatus(s);
 }
 
 /**
  * Create "503 Service Unavailable" or "504 Gateway Timeout" error depending
  * on whether this is a validation request. RFC 2616 says that we MUST reply
  * with "504 Gateway Timeout" if validation fails and cached reply has
  * proxy-revalidate, must-revalidate or s-maxage Cache-Control directive.
  */
 ErrorState *
 FwdState::makeConnectingError(const err_type type) const
 {
-    return errorCon(type, request->flags.need_validation ?
-                    HTTP_GATEWAY_TIMEOUT : HTTP_SERVICE_UNAVAILABLE, request);
+    return new ErrorState(type, request->flags.need_validation ?
+                          HTTP_GATEWAY_TIMEOUT : HTTP_SERVICE_UNAVAILABLE, request);
 }
 
 static void
 fwdStats(StoreEntry * s)
 {
     int i;
     int j;
     storeAppendPrintf(s, "Status");
 
-    for (j = 0; j <= MAX_FWD_STATS_IDX; j++) {
-        storeAppendPrintf(s, "\ttry#%d", j + 1);
+    for (j = 1; j < MAX_FWD_STATS_IDX; ++j) {
+        storeAppendPrintf(s, "\ttry#%d", j);
     }
 
     storeAppendPrintf(s, "\n");
 
-    for (i = 0; i <= (int) HTTP_INVALID_HEADER; i++) {
+    for (i = 0; i <= (int) HTTP_INVALID_HEADER; ++i) {
         if (FwdReplyCodes[0][i] == 0)
             continue;
 
         storeAppendPrintf(s, "%3d", i);
 
-        for (j = 0; j <= MAX_FWD_STATS_IDX; j++) {
+        for (j = 0; j <= MAX_FWD_STATS_IDX; ++j) {
             storeAppendPrintf(s, "\t%d", FwdReplyCodes[j][i]);
         }
 
         storeAppendPrintf(s, "\n");
     }
 }
