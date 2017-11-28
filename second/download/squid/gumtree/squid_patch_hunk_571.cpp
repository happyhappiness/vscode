 /* build request prefix and append it to a given MemBuf;
  * return the length of the prefix */
 mb_size_t
 HttpStateData::buildRequestPrefix(MemBuf * mb)
 {
     const int offset = mb->size;
-    HttpVersion httpver(1,1);
+    /* Uses a local httpver variable to print the HTTP/1.1 label
+     * since the HttpRequest may have an older version label.
+     * XXX: This could create protocol bugs as the headers sent and
+     * flow control should all be based on the HttpRequest version
+     * not the one we are sending. Needs checking.
+     */
+    Http::ProtocolVersion httpver(1,1);
     const char * url;
     if (_peer && !_peer->options.originserver)
-        url = entry->url();
+        url = urlCanonical(request);
     else
         url = request->urlpath.termedBuf();
     mb->Printf("%s %s %s/%d.%d\r\n",
                RequestMethodStr(request->method),
                url && *url ? url : "/",
                AnyP::ProtocolType_str[httpver.protocol],
