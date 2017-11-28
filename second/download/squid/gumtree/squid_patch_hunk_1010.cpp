      *
      \par
      * This needs to fall through - if we're unlucky and parse the _last_ request
      * from our read buffer we may never re-register for another client read.
      */
 
-    if (conn->clientParseRequests()) {
-        debugs(33, 3, HERE << conn->clientConnection << ": parsed next request from buffer");
+    if (clientParseRequests()) {
+        debugs(33, 3, clientConnection << ": parsed next request from buffer");
     }
 
     /** \par
      * Either we need to kick-start another read or, if we have
      * a half-closed connection, kill it after the last request.
      * This saves waiting for half-closed connections to finished being
      * half-closed _AND_ then, sometimes, spending "Timeout" time in
      * the keepalive "Waiting for next request" state.
      */
-    if (commIsHalfClosed(conn->clientConnection->fd) && (conn->getConcurrentRequestCount() == 0)) {
-        debugs(33, 3, "ClientSocketContext::keepaliveNextRequest: half-closed client with no pending requests, closing");
-        conn->clientConnection->close();
+    if (commIsHalfClosed(clientConnection->fd) && pipeline.empty()) {
+        debugs(33, 3, "half-closed client with no pending requests, closing");
+        clientConnection->close();
         return;
     }
 
-    ClientSocketContext::Pointer deferredRequest;
-
     /** \par
      * At this point we either have a parsed request (which we've
      * kicked off the processing for) or not. If we have a deferred
      * request (parsed but deferred for pipeling processing reasons)
      * then look at processing it. If not, simply kickstart
      * another read.
      */
-
-    if ((deferredRequest = conn->getCurrentContext()).getRaw()) {
-        debugs(33, 3, HERE << conn->clientConnection << ": calling PushDeferredIfNeeded");
-        ClientSocketContextPushDeferredIfNeeded(deferredRequest, conn);
-    } else if (conn->flags.readMore) {
-        debugs(33, 3, HERE << conn->clientConnection << ": calling conn->readNextRequest()");
-        conn->readNextRequest();
+    Http::StreamPointer deferredRequest = pipeline.front();
+    if (deferredRequest != nullptr) {
+        debugs(33, 3, clientConnection << ": calling PushDeferredIfNeeded");
+        ClientSocketContextPushDeferredIfNeeded(deferredRequest, this);
+    } else if (flags.readMore) {
+        debugs(33, 3, clientConnection << ": calling readNextRequest()");
+        readNextRequest();
     } else {
         // XXX: Can this happen? CONNECT tunnels have deferredRequest set.
-        debugs(33, DBG_IMPORTANT, HERE << "abandoning " << conn->clientConnection);
+        debugs(33, DBG_IMPORTANT, MYNAME << "abandoning " << clientConnection);
     }
 }
 
 void
-clientUpdateSocketStats(LogTags logType, size_t size)
-{
-    if (size == 0)
-        return;
-
-    kb_incr(&statCounter.client_http.kbytes_out, size);
-
-    if (logTypeIsATcpHit(logType))
-        kb_incr(&statCounter.client_http.hit_kbytes_out, size);
-}
-
-/**
- * increments iterator "i"
- * used by clientPackMoreRanges
- *
- \retval true    there is still data available to pack more ranges
- \retval false
- */
-bool
-ClientSocketContext::canPackMoreRanges() const
-{
-    /** first update iterator "i" if needed */
-
-    if (!http->range_iter.debt()) {
-        debugs(33, 5, HERE << "At end of current range spec for " << clientConnection);
-
-        if (http->range_iter.pos != http->range_iter.end)
-            ++http->range_iter.pos;
-
-        http->range_iter.updateSpec();
-    }
-
-    assert(!http->range_iter.debt() == !http->range_iter.currentSpec());
-
-    /* paranoid sync condition */
-    /* continue condition: need_more_data */
-    debugs(33, 5, "ClientSocketContext::canPackMoreRanges: returning " << (http->range_iter.currentSpec() ? true : false));
-    return http->range_iter.currentSpec() ? true : false;
-}
-
-int64_t
-ClientSocketContext::getNextRangeOffset() const
-{
-    debugs (33, 5, "range: " << http->request->range <<
-            "; http offset " << http->out.offset <<
-            "; reply " << reply);
-
-    // XXX: This method is called from many places, including pullData() which
-    // may be called before prepareReply() [on some Squid-generated errors].
-    // Hence, we may not even know yet whether we should honor/do ranges.
-
-    if (http->request->range) {
-        /* offset in range specs does not count the prefix of an http msg */
-        /* check: reply was parsed and range iterator was initialized */
-        assert(http->range_iter.valid);
-        /* filter out data according to range specs */
-        assert (canPackMoreRanges());
-        {
-            int64_t start;      /* offset of still missing data */
-            assert(http->range_iter.currentSpec());
-            start = http->range_iter.currentSpec()->offset + http->range_iter.currentSpec()->length - http->range_iter.debt();
-            debugs(33, 3, "clientPackMoreRanges: in:  offset: " << http->out.offset);
-            debugs(33, 3, "clientPackMoreRanges: out:"
-                   " start: " << start <<
-                   " spec[" << http->range_iter.pos - http->request->range->begin() << "]:" <<
-                   " [" << http->range_iter.currentSpec()->offset <<
-                   ", " << http->range_iter.currentSpec()->offset + http->range_iter.currentSpec()->length << "),"
-                   " len: " << http->range_iter.currentSpec()->length <<
-                   " debt: " << http->range_iter.debt());
-            if (http->range_iter.currentSpec()->length != -1)
-                assert(http->out.offset <= start);  /* we did not miss it */
-
-            return start;
-        }
-
-    } else if (reply && reply->content_range) {
-        /* request does not have ranges, but reply does */
-        /** \todo FIXME: should use range_iter_pos on reply, as soon as reply->content_range
-         *        becomes HttpHdrRange rather than HttpHdrRangeSpec.
-         */
-        return http->out.offset + reply->content_range->spec.offset;
-    }
-
-    return http->out.offset;
-}
-
-void
-ClientSocketContext::pullData()
-{
-    debugs(33, 5, reply << " written " << http->out.size << " into " << clientConnection);
-
-    /* More data will be coming from the stream. */
-    StoreIOBuffer readBuffer;
-    /* XXX: Next requested byte in the range sequence */
-    /* XXX: length = getmaximumrangelenfgth */
-    readBuffer.offset = getNextRangeOffset();
-    readBuffer.length = HTTP_REQBUF_SZ;
-    readBuffer.data = reqbuf;
-    /* we may note we have reached the end of the wanted ranges */
-    clientStreamRead(getTail(), http, readBuffer);
-}
-
-/** Adapt stream status to account for Range cases
- *
- */
-clientStream_status_t
-ClientSocketContext::socketState()
-{
-    switch (clientStreamStatus(getTail(), http)) {
-
-    case STREAM_NONE:
-        /* check for range support ending */
-
-        if (http->request->range) {
-            /* check: reply was parsed and range iterator was initialized */
-            assert(http->range_iter.valid);
-            /* filter out data according to range specs */
-
-            if (!canPackMoreRanges()) {
-                debugs(33, 5, HERE << "Range request at end of returnable " <<
-                       "range sequence on " << clientConnection);
-                // we got everything we wanted from the store
-                return STREAM_COMPLETE;
-            }
-        } else if (reply && reply->content_range) {
-            /* reply has content-range, but Squid is not managing ranges */
-            const int64_t &bytesSent = http->out.offset;
-            const int64_t &bytesExpected = reply->content_range->spec.length;
-
-            debugs(33, 7, HERE << "body bytes sent vs. expected: " <<
-                   bytesSent << " ? " << bytesExpected << " (+" <<
-                   reply->content_range->spec.offset << ")");
-
-            // did we get at least what we expected, based on range specs?
-
-            if (bytesSent == bytesExpected) // got everything
-                return STREAM_COMPLETE;
-
-            if (bytesSent > bytesExpected) // Error: Sent more than expected
-                return STREAM_UNPLANNED_COMPLETE;
-        }
-
-        return STREAM_NONE;
-
-    case STREAM_COMPLETE:
-        return STREAM_COMPLETE;
-
-    case STREAM_UNPLANNED_COMPLETE:
-        return STREAM_UNPLANNED_COMPLETE;
-
-    case STREAM_FAILED:
-        return STREAM_FAILED;
-    }
-
-    fatal ("unreachable code\n");
-    return STREAM_NONE;
-}
-
-/**
- * A write has just completed to the client, or we have just realised there is
- * no more data to send.
- */
-void
-clientWriteComplete(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, Comm::Flag errflag, int xerrno, void *data)
-{
-    ClientSocketContext *context = (ClientSocketContext *)data;
-    context->writeComplete(conn, bufnotused, size, errflag);
-}
-
-/// remembers the abnormal connection termination for logging purposes
-void
-ClientSocketContext::noteIoError(const int xerrno)
-{
-    if (http) {
-        if (xerrno == ETIMEDOUT)
-            http->al->http.timedout = true;
-        else // even if xerrno is zero (which means read abort/eof)
-            http->al->http.aborted = true;
-    }
-}
-
-void
-ClientSocketContext::doClose()
-{
-    clientConnection->close();
-}
-
-/// called when we encounter a response-related error
-void
-ClientSocketContext::initiateClose(const char *reason)
-{
-    http->getConn()->stopSending(reason); // closes ASAP
-}
-
-void
 ConnStateData::stopSending(const char *error)
 {
     debugs(33, 4, HERE << "sending error (" << clientConnection << "): " << error <<
            "; old receiving error: " <<
            (stoppedReceiving() ? stoppedReceiving_ : "none"));
 
