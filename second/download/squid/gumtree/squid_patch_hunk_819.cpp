     if (flags.keepalive) {
         hdr_out->putStr(HDR_CONNECTION, "keep-alive");
     }
 
     /* append Front-End-Https */
     if (flags.front_end_https) {
-        if (flags.front_end_https == 1 || request->protocol == AnyP::PROTO_HTTPS)
+        if (flags.front_end_https == 1 || request->url.getScheme() == AnyP::PROTO_HTTPS)
             hdr_out->putStr(HDR_FRONT_END_HTTPS, "On");
     }
 
     if (flags.chunked_request) {
         // Do not just copy the original value so that if the client-side
         // starts decode other encodings, this code may remain valid.
