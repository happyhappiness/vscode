     /* NOTREACHED */
 }
 
 /**
  * Decide where details need to be gathered to correctly describe a persistent connection.
  * What is needed:
- *  -  host name of server at other end of this link (either peer or requested host)
- *  -  port to which we connected the other end of this link (for peer or request)
- *  -  domain for which the connection is supposed to be used
- *  -  address of the client for which we made the connection
+ *  -  the address/port details about this link
+ *  -  domain name of server at other end of this link (either peer or requested host)
  */
 void
-FwdState::pconnPush(int fd, const peer *_peer, const HttpRequest *req, const char *domain, IpAddress &client_addr)
+FwdState::pconnPush(Comm::ConnectionPointer &conn, const char *domain)
 {
-    if (_peer) {
-        fwdPconnPool->push(fd, _peer->name, _peer->http_port, domain, client_addr);
+    if (conn->getPeer()) {
+        fwdPconnPool->push(conn, NULL);
     } else {
-        /* small performance improvement, using NULL for domain instead of listing it twice */
-        /* although this will leave a gap open for url-rewritten domains to share a link */
-        fwdPconnPool->push(fd, req->GetHost(), req->port, NULL, client_addr);
+        fwdPconnPool->push(conn, domain);
     }
 }
 
 void
 FwdState::initModule()
 {
-    memDataInit(MEM_FWD_SERVER, "FwdServer", sizeof(FwdServer), 0);
-
-#if WIP_FWD_LOG
-
-    if (logfile)
-        (void) 0;
-    else if (NULL == Config.Log.forward)
-        (void) 0;
-    else
-        logfile = logfileOpen(Config.Log.forward, 0, 1);
-
-#endif
-
     RegisterWithCacheManager();
 }
 
 void
 FwdState::RegisterWithCacheManager(void)
 {
-    CacheManager::GetInstance()->
-    registerAction("forward", "Request Forwarding Statistics", fwdStats, 0, 1);
+    Mgr::RegisterAction("forward", "Request Forwarding Statistics", fwdStats, 0, 1);
 }
 
 void
 FwdState::logReplyStatus(int tries, http_status status)
 {
     if (status > HTTP_INVALID_HEADER)
         return;
 
-    assert(tries);
-
-    tries--;
+    assert(tries >= 0);
 
     if (tries > MAX_FWD_STATS_IDX)
         tries = MAX_FWD_STATS_IDX;
 
-    FwdReplyCodes[tries][status]++;
-}
-
-void
-FwdState::serversFree(FwdServer ** FSVR)
-{
-    FwdServer *fs;
-
-    while ((fs = *FSVR)) {
-        *FSVR = fs->next;
-        fwdServerFree(fs);
-    }
-}
-
-/** From Comment #5 by Henrik Nordstrom made at
-http://www.squid-cache.org/bugs/show_bug.cgi?id=2391 on 2008-09-19
-
-updateHierarchyInfo should be called each time a new path has been
-selected or when more information about the path is available (i.e. the
-server IP), and when it's called it needs to be given reasonable
-arguments describing the now selected path..
-
-It does not matter from a functional perspective if it gets called a few
-times more than what is really needed, but calling it too often may
-obviously hurt performance.
-*/
-// updates HierarchyLogEntry, guessing nextHop and its format
-void
-FwdState::updateHierarchyInfo()
-{
-    assert(request);
-
-    FwdServer *fs = servers;
-    assert(fs);
-
-    const char *nextHop = NULL;
-
-    if (fs->_peer) {
-        // went to peer, log peer host name
-        nextHop = fs->_peer->name;
-    } else {
-        // went DIRECT, must honor log_ip_on_direct
-
-        // XXX: or should we use request->host_addr here? how?
-        assert(server_fd >= 0);
-        nextHop = fd_table[server_fd].ipaddr;
-        if (!Config.onoff.log_ip_on_direct || !nextHop[0])
-            nextHop = request->GetHost(); // domain name
-    }
-
-    assert(nextHop);
-    hierarchyNote(&request->hier, fs->code, nextHop);
+    ++ FwdReplyCodes[tries][status];
 }
 
-
 /**** PRIVATE NON-MEMBER FUNCTIONS ********************************************/
 
-static void
-fwdServerFree(FwdServer * fs)
-{
-    cbdataReferenceDone(fs->_peer);
-    memFree(fs, MEM_FWD_SERVER);
-}
-
-static IpAddress
-aclMapAddr(acl_address * head, ACLChecklist * ch)
-{
-    acl_address *l;
-
-    IpAddress addr;
-
-    for (l = head; l; l = l->next) {
-        if (!l->aclList || ch->matchAclListFast(l->aclList))
-            return l->addr;
-    }
-
-    addr.SetAnyAddr();
-    return addr;
-}
-
 /*
  * DPW 2007-05-19
  * Formerly static, but now used by client_side_request.cc
  */
-int
+/// Checks for a TOS value to apply depending on the ACL
+tos_t
 aclMapTOS(acl_tos * head, ACLChecklist * ch)
 {
     acl_tos *l;
 
     for (l = head; l; l = l->next) {
-        if (!l->aclList || ch->matchAclListFast(l->aclList))
+        if (!l->aclList || ch->fastCheck(l->aclList) == ACCESS_ALLOWED)
             return l->tos;
     }
 
     return 0;
 }
 
-IpAddress
-getOutgoingAddr(HttpRequest * request, struct peer *dst_peer)
+/// Checks for a netfilter mark value to apply depending on the ACL
+nfmark_t
+aclMapNfmark(acl_nfmark * head, ACLChecklist * ch)
 {
-    if (request && request->flags.spoof_client_ip) {
-        if (!dst_peer || !dst_peer->options.no_tproxy)
-            return request->client_addr;
-        // else no tproxy today ...
-    }
-
-    if (!Config.accessList.outgoing_address) {
-        return IpAddress(); // anything will do.
-    }
+    acl_nfmark *l;
 
-    ACLFilledChecklist ch(NULL, request, NULL);
-    ch.dst_peer = dst_peer;
-
-    if (request) {
-#if FOLLOW_X_FORWARDED_FOR
-        if (Config.onoff.acl_uses_indirect_client)
-            ch.src_addr = request->indirect_client_addr;
-        else
-#endif
-            ch.src_addr = request->client_addr;
-        ch.my_addr = request->my_addr;
+    for (l = head; l; l = l->next) {
+        if (!l->aclList || ch->fastCheck(l->aclList) == ACCESS_ALLOWED)
+            return l->nfmark;
     }
 
-    return aclMapAddr(Config.accessList.outgoing_address, &ch);
+    return 0;
 }
 
-unsigned long
-getOutgoingTOS(HttpRequest * request)
+void
+getOutgoingAddress(HttpRequest * request, Comm::ConnectionPointer conn)
 {
-    ACLFilledChecklist ch(NULL, request, NULL);
+    // skip if an outgoing address is already set.
+    if (!conn->local.IsAnyAddr()) return;
 
-    if (request) {
-        ch.src_addr = request->client_addr;
-        ch.my_addr = request->my_addr;
-    }
+    // ensure that at minimum the wildcard local matches remote protocol
+    if (conn->remote.IsIPv4())
+        conn->local.SetIPv4();
 
-    return aclMapTOS(Config.accessList.outgoing_tos, &ch);
-}
+    // maybe use TPROXY client address
+    if (request && request->flags.spoof_client_ip) {
+        if (!conn->getPeer() || !conn->getPeer()->options.no_tproxy) {
+#if FOLLOW_X_FORWARDED_FOR && LINUX_NETFILTER
+            if (Config.onoff.tproxy_uses_indirect_client)
+                conn->local = request->indirect_client_addr;
+            else
+#endif
+                conn->local = request->client_addr;
+            // some flags need setting on the socket to use this address
+            conn->flags |= COMM_DOBIND;
+            conn->flags |= COMM_TRANSPARENT;
+            return;
+        }
+        // else no tproxy today ...
+    }
 
+    if (!Config.accessList.outgoing_address) {
+        return; // anything will do.
+    }
 
-/**** WIP_FWD_LOG *************************************************************/
+    ACLFilledChecklist ch(NULL, request, NULL);
+    ch.dst_peer = conn->getPeer();
+    ch.dst_addr = conn->remote;
 
-#if WIP_FWD_LOG
-void
-fwdUninit(void)
-{
-    if (NULL == logfile)
-        return;
+    // TODO use the connection details in ACL.
+    // needs a bit of rework in ACLFilledChecklist to use Comm::Connection instead of ConnStateData
 
-    logfileClose(logfile);
+    acl_address *l;
+    for (l = Config.accessList.outgoing_address; l; l = l->next) {
 
-    logfile = NULL;
-}
+        /* check if the outgoing address is usable to the destination */
+        if (conn->remote.IsIPv4() != l->addr.IsIPv4()) continue;
 
-void
-fwdLogRotate(void)
-{
-    if (logfile)
-        logfileRotate(logfile);
+        /* check ACLs for this outgoing address */
+        if (!l->aclList || ch.fastCheck(l->aclList) == ACCESS_ALLOWED) {
+            conn->local = l->addr;
+            return;
+        }
+    }
 }
 
-static void
-FwdState::log()
+tos_t
+GetTosToServer(HttpRequest * request)
 {
-    if (NULL == logfile)
-        return;
-
-    logfilePrintf(logfile, "%9d.%03d %03d %s %s\n",
-                  (int) current_time.tv_sec,
-                  (int) current_time.tv_usec / 1000,
-                  last_status,
-                  RequestMethodStr(request->method),
-                  request->canonical);
+    ACLFilledChecklist ch(NULL, request, NULL);
+    return aclMapTOS(Ip::Qos::TheConfig.tosToServer, &ch);
 }
 
-void
-FwdState::status(http_status s)
+nfmark_t
+GetNfmarkToServer(HttpRequest * request)
 {
-    last_status = s;
+    ACLFilledChecklist ch(NULL, request, NULL);
+    return aclMapNfmark(Ip::Qos::TheConfig.nfmarkToServer, &ch);
 }
-
-#endif
