     if (req_time <= squid_curtime)
         peerDigestRequest(pd);  /* will set pd->flags.requested */
     else
         peerDigestSetCheck(pd, req_time - squid_curtime);
 }
 
-CBDATA_TYPE(DigestFetchState);
-
 /* ask store for a digest */
 static void
 peerDigestRequest(PeerDigest * pd)
 {
     CachePeer *p = pd->peer;
     StoreEntry *e, *old_e;
     char *url = NULL;
     const cache_key *key;
     HttpRequest *req;
-    DigestFetchState *fetch = NULL;
     StoreIOBuffer tempBuffer;
 
     pd->req_result = NULL;
     pd->flags.requested = true;
 
     /* compute future request components */
 
     if (p->digest_url)
         url = xstrdup(p->digest_url);
     else
-        url = xstrdup(internalRemoteUri(p->host, p->http_port, "/squid-internal-periodic/", StoreDigestFileName));
+        url = xstrdup(internalRemoteUri(p->host, p->http_port, "/squid-internal-periodic/", SBuf(StoreDigestFileName)));
 
     req = HttpRequest::CreateFromUrl(url);
 
     assert(req);
 
     key = storeKeyPublicByRequest(req);
 
     debugs(72, 2, "peerDigestRequest: " << url << " key: " << storeKeyText(key));
 
     /* add custom headers */
     assert(!req->header.len);
 
-    req->header.putStr(HDR_ACCEPT, StoreDigestMimeStr);
+    req->header.putStr(Http::HdrType::ACCEPT, StoreDigestMimeStr);
 
-    req->header.putStr(HDR_ACCEPT, "text/html");
+    req->header.putStr(Http::HdrType::ACCEPT, "text/html");
 
     if (p->login &&
             p->login[0] != '*' &&
             strcmp(p->login, "PASS") != 0 &&
             strcmp(p->login, "PASSTHRU") != 0 &&
             strncmp(p->login, "NEGOTIATE",9) != 0 &&
             strcmp(p->login, "PROXYPASS") != 0) {
-        xstrncpy(req->login, p->login, MAX_LOGIN_SZ);
+        req->url.userInfo(SBuf(p->login)); // XXX: performance regression make peer login SBuf as well.
     }
     /* create fetch state structure */
-    CBDATA_INIT_TYPE(DigestFetchState);
-
-    fetch = cbdataAlloc(DigestFetchState);
-
-    fetch->request = req;
-    HTTPMSGLOCK(fetch->request);
-
-    fetch->pd = cbdataReference(pd);
-
-    fetch->offset = 0;
-
-    fetch->state = DIGEST_READ_REPLY;
+    DigestFetchState *fetch = new DigestFetchState(pd, req);
 
     /* update timestamps */
-    fetch->start_time = squid_curtime;
-
     pd->times.requested = squid_curtime;
-
     pd_last_req_time = squid_curtime;
-
     req->flags.cachable = true;
 
     /* the rest is based on clientProcessExpired() */
     req->flags.refresh = true;
 
     old_e = fetch->old_entry = Store::Root().get(key);
