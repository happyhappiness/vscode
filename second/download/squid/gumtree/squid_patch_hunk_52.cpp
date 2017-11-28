 {
     const Adaptation::Service &s = service();
     const String uri = s.cfg().uri;
     buf.Printf("OPTIONS " SQUIDSTRINGPH " ICAP/1.0\r\n", SQUIDSTRINGPRINT(uri));
     const String host = s.cfg().host;
     buf.Printf("Host: " SQUIDSTRINGPH ":%d\r\n", SQUIDSTRINGPRINT(host), s.cfg().port);
+    if (TheConfig.allow206_enable)
+        buf.Printf("Allow: 206\r\n");
     buf.append(ICAP::crlf, 2);
 
     // XXX: HttpRequest cannot fully parse ICAP Request-Line
     http_status reqStatus;
     Must(icapRequest->parse(&buf, true, &reqStatus) > 0);
 }
