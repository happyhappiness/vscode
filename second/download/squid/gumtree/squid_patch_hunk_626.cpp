     HttpReply rep;
     Http::StatusCode parseErr = Http::scNone;
     const bool eof = !chunkSize;
     const bool parsed = rep.parse(connectRespBuf, eof, &parseErr);
     if (!parsed) {
         if (parseErr > 0) { // unrecoverable parsing error
-            server.logicError("malformed CONNECT response from peer");
+            informUserOfPeerError("malformed CONNECT response from peer");
             return;
         }
 
         // need more data
         assert(!eof);
         assert(!parseErr);
 
         if (!connectRespBuf->hasSpace()) {
-            server.logicError("huge CONNECT response from peer");
+            informUserOfPeerError("huge CONNECT response from peer");
             return;
         }
 
         // keep reading
         readConnectResponse();
         return;
