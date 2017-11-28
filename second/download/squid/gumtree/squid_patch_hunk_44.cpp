     BodyPipeCheckout bpc(*adapted.body_pipe);
     const bool parsed = bodyParser->parse(&readBuf, &bpc.buf);
     bpc.checkIn();
 
     debugs(93, 5, HERE << "have " << readBuf.contentSize() << " body bytes after " <<
            "parse; parsed all: " << parsed);
-    replyBodySize += adapted.body_pipe->buf().contentSize();
+    replyHttpBodySize += adapted.body_pipe->buf().contentSize();
 
     // TODO: expose BodyPipe::putSize() to make this check simpler and clearer
     // TODO: do we really need this if we disable when sending headers?
     if (adapted.body_pipe->buf().contentSize() > 0) { // parsed something sometime
         disableRepeats("sent adapted content");
         disableBypass("sent adapted content", true);
     }
 
     if (parsed) {
+        if (state.readyForUob && bodyParser->useOriginBody >= 0) {
+            prepPartialBodyEchoing(
+                static_cast<uint64_t>(bodyParser->useOriginBody));
+            stopParsing();
+            return;
+        }
+
         stopParsing();
         stopSending(true); // the parser succeeds only if all parsed data fits
         return;
     }
 
     debugs(93,3,HERE << this << " needsMoreData = " << bodyParser->needsMoreData());
