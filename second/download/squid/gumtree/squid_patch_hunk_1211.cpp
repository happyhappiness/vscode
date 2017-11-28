     // is optimized, reuse server.buf for CONNEC response accumulation instead.
 
     /* mimic the basic parts of HttpStateData::processReplyHeader() */
     HttpReply rep;
     Http::StatusCode parseErr = Http::scNone;
     const bool eof = !chunkSize;
-    const bool parsed = rep.parse(connectRespBuf, eof, &parseErr);
+    connectRespBuf->terminate(); // HttpMsg::parse requires terminated string
+    const bool parsed = rep.parse(connectRespBuf->content(), connectRespBuf->contentSize(), eof, &parseErr);
     if (!parsed) {
         if (parseErr > 0) { // unrecoverable parsing error
             informUserOfPeerError("malformed CONNECT response from peer", 0);
             return;
         }
 
