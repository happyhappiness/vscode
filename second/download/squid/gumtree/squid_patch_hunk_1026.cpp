         authenticateFixHeader(reply, request->auth_user_request, request, 0, 1);
     } else if (request->auth_user_request != NULL)
         authenticateFixHeader(reply, request->auth_user_request, request, http->flags.accel, 0);
 #endif
 
     /* Append X-Cache */
-    httpHeaderPutStrf(hdr, HDR_X_CACHE, "%s from %s",
+    httpHeaderPutStrf(hdr, Http::HdrType::X_CACHE, "%s from %s",
                       is_hit ? "HIT" : "MISS", getMyHostname());
 
 #if USE_CACHE_DIGESTS
     /* Append X-Cache-Lookup: -- temporary hack, to be removed @?@ @?@ */
-    httpHeaderPutStrf(hdr, HDR_X_CACHE_LOOKUP, "%s from %s:%d",
+    httpHeaderPutStrf(hdr, Http::HdrType::X_CACHE_LOOKUP, "%s from %s:%d",
                       lookup_type ? lookup_type : "NONE",
                       getMyHostname(), getMyPort());
 
 #endif
 
     const bool maySendChunkedReply = !request->multipartRangeRequest() &&
                                      reply->sline.protocol == AnyP::PROTO_HTTP && // response is HTTP
-                                     (request->http_ver >= Http::ProtocolVersion(1, 1));
+                                     (request->http_ver >= Http::ProtocolVersion(1,1));
 
     /* Check whether we should send keep-alive */
     if (!Config.onoff.error_pconns && reply->sline.status() >= 400 && !request->flags.mustKeepalive) {
         debugs(33, 3, "clientBuildReplyHeader: Error, don't keep-alive");
         request->flags.proxyKeepalive = false;
     } else if (!Config.onoff.client_pconns && !request->flags.mustKeepalive) {
