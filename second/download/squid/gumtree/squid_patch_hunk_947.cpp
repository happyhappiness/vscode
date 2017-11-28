 }
 
 void Adaptation::Icap::OptXact::makeRequest(MemBuf &buf)
 {
     const Adaptation::Service &s = service();
     const String uri = s.cfg().uri;
-    buf.Printf("OPTIONS " SQUIDSTRINGPH " ICAP/1.0\r\n", SQUIDSTRINGPRINT(uri));
+    buf.appendf("OPTIONS " SQUIDSTRINGPH " ICAP/1.0\r\n", SQUIDSTRINGPRINT(uri));
     const String host = s.cfg().host;
-    buf.Printf("Host: " SQUIDSTRINGPH ":%d\r\n", SQUIDSTRINGPRINT(host), s.cfg().port);
+    buf.appendf("Host: " SQUIDSTRINGPH ":%d\r\n", SQUIDSTRINGPRINT(host), s.cfg().port);
 
     if (!TheConfig.reuse_connections)
-        buf.Printf("Connection: close\r\n");
+        buf.append("Connection: close\r\n", 19);
 
     if (TheConfig.allow206_enable)
-        buf.Printf("Allow: 206\r\n");
+        buf.append("Allow: 206\r\n", 12);
     buf.append(ICAP::crlf, 2);
 
     // XXX: HttpRequest cannot fully parse ICAP Request-Line
     Http::StatusCode reqStatus;
-    Must(icapRequest->parse(&buf, true, &reqStatus) > 0);
+    buf.terminate(); // HttpMsg::parse requires terminated buffer
+    Must(icapRequest->parse(buf.content(), buf.contentSize(), true, &reqStatus) > 0);
 }
 
 void Adaptation::Icap::OptXact::handleCommWrote(size_t size)
 {
     debugs(93, 9, HERE << "finished writing " << size <<
            "-byte request " << status());
