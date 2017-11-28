 
         delete cc;
     }
 
     /* maybe append Connection: keep-alive */
     if (flags.keepalive) {
-        hdr_out->putStr(HDR_CONNECTION, "keep-alive");
+        hdr_out->putStr(Http::HdrType::CONNECTION, "keep-alive");
     }
 
     /* append Front-End-Https */
     if (flags.front_end_https) {
         if (flags.front_end_https == 1 || request->url.getScheme() == AnyP::PROTO_HTTPS)
-            hdr_out->putStr(HDR_FRONT_END_HTTPS, "On");
+            hdr_out->putStr(Http::HdrType::FRONT_END_HTTPS, "On");
     }
 
     if (flags.chunked_request) {
         // Do not just copy the original value so that if the client-side
         // starts decode other encodings, this code may remain valid.
-        hdr_out->putStr(HDR_TRANSFER_ENCODING, "chunked");
+        hdr_out->putStr(Http::HdrType::TRANSFER_ENCODING, "chunked");
     }
 
     /* Now mangle the headers. */
-    if (Config2.onoff.mangle_request_headers)
-        httpHdrMangleList(hdr_out, request, ROR_REQUEST);
-
-    if (Config.request_header_add && !Config.request_header_add->empty())
-        httpHdrAdd(hdr_out, request, al, *Config.request_header_add);
+    httpHdrMangleList(hdr_out, request, al, ROR_REQUEST);
 
     strConnection.clean();
 }
 
 /**
  * Decides whether a particular header may be cloned from the received Clients request
  * to our outgoing fetch request.
  */
 void
-copyOneHeaderFromClientsideRequestToUpstreamRequest(const HttpHeaderEntry *e, const String strConnection, const HttpRequest * request, HttpHeader * hdr_out, const int we_do_ranges, const HttpStateFlags &flags)
+copyOneHeaderFromClientsideRequestToUpstreamRequest(const HttpHeaderEntry *e, const String strConnection, const HttpRequest * request, HttpHeader * hdr_out, const int we_do_ranges, const Http::StateFlags &flags)
 {
     debugs(11, 5, "httpBuildRequestHeader: " << e->name << ": " << e->value );
 
     switch (e->id) {
 
     /** \par RFC 2616 sect 13.5.1 - Hop-by-Hop headers which Squid should not pass on. */
 
-    case HDR_PROXY_AUTHORIZATION:
+    case Http::HdrType::PROXY_AUTHORIZATION:
         /** \par Proxy-Authorization:
          * Only pass on proxy authentication to peers for which
          * authentication forwarding is explicitly enabled
          */
         if (!flags.originpeer && flags.proxying && request->peer_login &&
                 (strcmp(request->peer_login, "PASS") == 0 ||
