         if (TheConfig.use_indirect_client) {
             client_addr = request->indirect_client_addr;
         } else
 #endif
             client_addr = request->client_addr;
         if (!client_addr.isAnyAddr() && !client_addr.isNoAddr())
-            buf.Printf("X-Client-IP: %s\r\n", client_addr.toStr(ntoabuf,MAX_IPSTRLEN));
+            buf.appendf("X-Client-IP: %s\r\n", client_addr.toStr(ntoabuf,MAX_IPSTRLEN));
     }
 
     if (TheConfig.send_username && request)
         makeUsernameHeader(request, buf);
 
     // Adaptation::Config::metaHeaders
