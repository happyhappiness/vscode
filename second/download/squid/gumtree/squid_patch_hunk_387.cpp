 
     default:
         fatal("Hit unreachable code in clientWriteComplete\n");
     }
 }
 
-extern "C" CSR clientGetMoreData;
-extern "C" CSS clientReplyStatus;
-extern "C" CSD clientReplyDetach;
+SQUIDCEXTERN CSR clientGetMoreData;
+SQUIDCEXTERN CSS clientReplyStatus;
+SQUIDCEXTERN CSD clientReplyDetach;
 
 static ClientSocketContext *
 parseHttpRequestAbort(ConnStateData * csd, const char *uri)
 {
     ClientHttpRequest *http;
     ClientSocketContext *context;
