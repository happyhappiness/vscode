     httpHeaderPutStrf(hdr, HDR_X_CACHE_LOOKUP, "%s from %s:%d",
                       lookup_type ? lookup_type : "NONE",
                       getMyHostname(), getMyPort());
 
 #endif
 
+    // XXX: chunking a Content-Range response may not violate specs, but our
+    // ClientSocketContext::writeComplete() confuses the end of ClientStream
+    // with the end of to-client writing and may quit before writing last-chunk
+    const bool maySendChunkedReply = !reply->content_range &&
+                                     !request->multipartRangeRequest() &&
+                                     reply->sline.protocol == AnyP::PROTO_HTTP && // response is HTTP
+                                     (request->http_ver >= HttpVersion(1, 1));
+
     /* Check whether we should send keep-alive */
     if (!Config.onoff.error_pconns && reply->sline.status >= 400 && !request->flags.must_keepalive) {
         debugs(33, 3, "clientBuildReplyHeader: Error, don't keep-alive");
         request->flags.proxy_keepalive = 0;
     } else if (!Config.onoff.client_pconns && !request->flags.must_keepalive) {
         debugs(33, 2, "clientBuildReplyHeader: Connection Keep-Alive not requested by admin or client");
