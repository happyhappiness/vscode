     if (clen < 0)
         return INCOMPLETE_MSG;
 
     /** \par
      * If the body size is known, we must wait until we've gotten all of it. */
     if (clen > 0) {
-        // old technique:
-        // if (entry->mem_obj->endOffset() < vrep->content_length + vrep->hdr_sz)
-        const int64_t body_bytes_read = reply_bytes_read - header_bytes_read;
-        debugs(11,5, "persistentConnStatus: body_bytes_read=" <<
-               body_bytes_read << " content_length=" << vrep->content_length);
+        debugs(11,5, "payloadSeen=" << payloadSeen << " content_length=" << vrep->content_length);
 
-        if (body_bytes_read < vrep->content_length)
+        if (payloadSeen < vrep->content_length)
             return INCOMPLETE_MSG;
 
-        if (body_bytes_truncated > 0) // already read more than needed
+        if (payloadTruncated > 0) // already read more than needed
             return COMPLETE_NONPERSISTENT_MSG; // disable pconns
     }
 
     /** \par
      * If there is no message body or we got it all, we can be persistent */
     return statusIfComplete();
 }
 
-/*
- * This is the callback after some data has been read from the network
- */
-/*
-void
-HttpStateData::ReadReplyWrapper(int fd, char *buf, size_t len, Comm::Flag flag, int xerrno, void *data)
+static void
+readDelayed(void *context, CommRead const &)
 {
-    HttpStateData *httpState = static_cast<HttpStateData *>(data);
-    assert (fd == httpState->serverConnection->fd);
-    // assert(buf == readBuf->content());
-    PROF_start(HttpStateData_readReply);
-    httpState->readReply(len, flag, xerrno);
-    PROF_stop(HttpStateData_readReply);
+    HttpStateData *state = static_cast<HttpStateData*>(context);
+    state->flags.do_next_read = true;
+    state->maybeReadVirginBody();
 }
-*/
 
-/* XXX this function is too long! */
 void
 HttpStateData::readReply(const CommIoCbParams &io)
 {
-    int bin;
-    int clen;
-    int len = io.size;
-
+    Must(!flags.do_next_read); // XXX: should have been set false by mayReadVirginBody()
     flags.do_next_read = false;
 
-    debugs(11, 5, HERE << io.conn << ": len " << len << ".");
+    debugs(11, 5, io.conn);
 
     // Bail out early on Comm::ERR_CLOSING - close handlers will tidy up for us
     if (io.flag == Comm::ERR_CLOSING) {
         debugs(11, 3, "http socket closing");
         return;
     }
 
     if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
         abortTransaction("store entry aborted while reading reply");
         return;
     }
 
-    // handle I/O errors
-    if (io.flag != Comm::OK || len < 0) {
-        debugs(11, 2, HERE << io.conn << ": read failure: " << xstrerror() << ".");
+    Must(Comm::IsConnOpen(serverConnection));
+    Must(io.conn->fd == serverConnection->fd);
 
-        if (ignoreErrno(io.xerrno)) {
-            flags.do_next_read = true;
-        } else {
-            ErrorState *err = new ErrorState(ERR_READ_ERROR, Http::scBadGateway, fwd->request);
-            err->xerrno = io.xerrno;
-            fwd->fail(err);
-            flags.do_next_read = false;
-            closeServer();
-            mustStop("HttpStateData::readReply");
-        }
+    /*
+     * Don't reset the timeout value here. The value should be
+     * counting Config.Timeout.request and applies to the request
+     * as a whole, not individual read() calls.
+     * Plus, it breaks our lame *HalfClosed() detection
+     */
+
+    Must(maybeMakeSpaceAvailable(true));
+    CommIoCbParams rd(this); // will be expanded with ReadNow results
+    rd.conn = io.conn;
+    rd.size = entry->bytesWanted(Range<size_t>(0, inBuf.spaceSize()));
 
+    if (rd.size <= 0) {
+        assert(entry->mem_obj);
+        AsyncCall::Pointer nilCall;
+        entry->mem_obj->delayRead(DeferredRead(readDelayed, this, CommRead(io.conn, NULL, 0, nilCall)));
         return;
     }
 
-    // update I/O stats
-    if (len > 0) {
-        readBuf->appended(len);
-        reply_bytes_read += len;
+    switch (Comm::ReadNow(rd, inBuf)) {
+    case Comm::INPROGRESS:
+        if (inBuf.isEmpty())
+            debugs(33, 2, io.conn << ": no data to process, " << xstrerr(rd.xerrno));
+        flags.do_next_read = true;
+        maybeReadVirginBody();
+        return;
+
+    case Comm::OK:
+    {
+        payloadSeen += rd.size;
 #if USE_DELAY_POOLS
         DelayId delayId = entry->mem_obj->mostBytesAllowed();
-        delayId.bytesIn(len);
+        delayId.bytesIn(rd.size);
 #endif
 
-        kb_incr(&(statCounter.server.all.kbytes_in), len);
-        kb_incr(&(statCounter.server.http.kbytes_in), len);
+        statCounter.server.all.kbytes_in += rd.size;
+        statCounter.server.http.kbytes_in += rd.size;
         ++ IOStats.Http.reads;
 
-        for (clen = len - 1, bin = 0; clen; ++bin)
+        int bin = 0;
+        for (int clen = rd.size - 1; clen; ++bin)
             clen >>= 1;
 
         ++ IOStats.Http.read_hist[bin];
 
         // update peer response time stats (%<pt)
         const timeval &sent = request->hier.peer_http_request_sent;
-        request->hier.peer_response_time =
-            sent.tv_sec ? tvSubMsec(sent, current_time) : -1;
+        if (sent.tv_sec)
+            tvSub(request->hier.peer_response_time, sent, current_time);
+        else
+            request->hier.peer_response_time.tv_sec = -1;
     }
 
-    /** \par
-     * Here the RFC says we should ignore whitespace between replies, but we can't as
-     * doing so breaks HTTP/0.9 replies beginning with witespace, and in addition
-     * the response splitting countermeasures is extremely likely to trigger on this,
-     * not allowing connection reuse in the first place.
-     *
-     * 2012-02-10: which RFC? not 2068 or 2616,
-     *     tolerance there is all about whitespace between requests and header tokens.
-     */
+        /* Continue to process previously read data */
+    break;
 
-    if (len == 0) { // reached EOF?
+    case Comm::ENDFILE: // close detected by 0-byte read
         eof = 1;
         flags.do_next_read = false;
 
-        /* Bug 2879: Replies may terminate with \r\n then EOF instead of \r\n\r\n
-         * Ensure here that we have at minimum two \r\n when EOF is seen.
-         * TODO: Add eof parameter to headersEnd() and move this hack there.
-         */
-        if (readBuf->contentSize() && !flags.headers_parsed) {
-            /*
-             * Yes Henrik, there is a point to doing this.  When we
-             * called httpProcessReplyHeader() before, we didn't find
-             * the end of headers, but now we are definately at EOF, so
-             * we want to process the reply headers.
-             */
-            /* Fake an "end-of-headers" to work around such broken servers */
-            readBuf->append("\r\n", 2);
-        }
+        /* Continue to process previously read data */
+        break;
+
+    // case Comm::COMM_ERROR:
+    default: // no other flags should ever occur
+        debugs(11, 2, io.conn << ": read failure: " << xstrerr(rd.xerrno));
+        ErrorState *err = new ErrorState(ERR_READ_ERROR, Http::scBadGateway, fwd->request);
+        err->xerrno = rd.xerrno;
+        fwd->fail(err);
+        flags.do_next_read = false;
+        closeServer();
+        mustStop("HttpStateData::readReply");
+        return;
     }
 
+    /* Process next response from buffer */
     processReply();
 }
 
 /// processes the already read and buffered response data, possibly after
 /// waiting for asynchronous 1xx control message processing
 void
