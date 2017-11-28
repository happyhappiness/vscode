     memset(&flags, '\0', sizeof(flags));
     flags.proxying = tunnelState->request->flags.proxying;
     MemBuf mb;
     mb.init();
     mb.Printf("CONNECT %s HTTP/1.1\r\n", tunnelState->url);
     HttpStateData::httpBuildRequestHeader(tunnelState->request.getRaw(),
-                                          NULL,			/* StoreEntry */
-                                          tunnelState->al,			/* AccessLogEntry */
+                                          NULL,         /* StoreEntry */
+                                          tunnelState->al,          /* AccessLogEntry */
                                           &hdr_out,
-                                          flags);			/* flags */
+                                          flags);           /* flags */
     packerToMemInit(&p, &mb);
     hdr_out.packInto(&p);
     hdr_out.clean();
     packerClean(&p);
     mb.append("\r\n", 2);
 
-    debugs(11, 2, "Tunnel Server REQUEST: " << tunnelState->server.conn << ":\n----------\n" <<
-           Raw("tunnelRelayConnectRequest", mb.content(), mb.contentSize()) << "\n----------");
+    debugs(11, 2, "Tunnel Server REQUEST: " << tunnelState->server.conn <<
+           ":\n----------\n" << mb.buf << "\n----------");
 
     AsyncCall::Pointer writeCall = commCbCall(5,5, "tunnelConnectReqWriteDone",
-                                   CommIoCbPtrFun(tunnelConnectReqWriteDone, tunnelState));
+                                   CommIoCbPtrFun(tunnelConnectReqWriteDone,
+                                           tunnelState));
 
     tunnelState->server.write(mb.buf, mb.size, writeCall, mb.freeFunc());
     tunnelState->connectReqWriting = true;
 
     tunnelState->connectRespBuf = new MemBuf;
     // SQUID_TCP_SO_RCVBUF: we should not accumulate more than regular I/O buffer
