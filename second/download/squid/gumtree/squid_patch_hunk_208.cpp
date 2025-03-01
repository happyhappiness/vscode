      *    - reply will be cachable
      * (If the reply will be uncachable we have to throw it away after
      *  serving this request, so it is better to forward ranges to
      *  the server and fetch only the requested content)
      */
 
-    if (NULL == orig_request->range || !orig_request->flags.cachable
-            || orig_request->range->offsetLimitExceeded() || orig_request->flags.connection_auth)
+    int64_t roffLimit = request->getRangeOffsetLimit();
+
+    if (NULL == request->range || !request->flags.cachable
+            || request->range->offsetLimitExceeded(roffLimit) || request->flags.connection_auth)
         result = false;
 
     debugs(11, 8, "decideIfWeDoRanges: range specs: " <<
-           orig_request->range << ", cachable: " <<
-           orig_request->flags.cachable << "; we_do_ranges: " << result);
+           request->range << ", cachable: " <<
+           request->flags.cachable << "; we_do_ranges: " << result);
 
     return result;
 }
 
 /* build request prefix and append it to a given MemBuf;
  * return the length of the prefix */
 mb_size_t
-HttpStateData::buildRequestPrefix(HttpRequest * aRequest,
-                                  HttpRequest * original_request,
-                                  StoreEntry * sentry,
-                                  MemBuf * mb)
+HttpStateData::buildRequestPrefix(MemBuf * mb)
 {
     const int offset = mb->size;
     HttpVersion httpver(1,1);
-    mb->Printf("%s %s HTTP/%d.%d\r\n",
-               RequestMethodStr(aRequest->method),
-               aRequest->urlpath.size() ? aRequest->urlpath.termedBuf() : "/",
+    const char * url;
+    if (_peer && !_peer->options.originserver)
+        url = entry->url();
+    else
+        url = request->urlpath.termedBuf();
+    mb->Printf("%s %s %s/%d.%d\r\n",
+               RequestMethodStr(request->method),
+               url && *url ? url : "/",
+               AnyP::ProtocolType_str[httpver.protocol],
                httpver.major,httpver.minor);
     /* build and pack headers */
     {
         HttpHeader hdr(hoRequest);
         Packer p;
-        httpBuildRequestHeader(aRequest, original_request, sentry, &hdr, flags);
+        httpBuildRequestHeader(request, entry, fwd->al, &hdr, flags);
 
-        if (aRequest->flags.pinned && aRequest->flags.connection_auth)
-            aRequest->flags.auth_sent = 1;
+        if (request->flags.pinned && request->flags.connection_auth)
+            request->flags.auth_sent = 1;
         else if (hdr.has(HDR_AUTHORIZATION))
-            aRequest->flags.auth_sent = 1;
+            request->flags.auth_sent = 1;
 
         packerToMemInit(&p, mb);
         hdr.packInto(&p);
         hdr.clean();
         packerClean(&p);
     }
