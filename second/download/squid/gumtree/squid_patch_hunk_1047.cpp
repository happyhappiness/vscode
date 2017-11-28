         } else if (ftp.server_msg) {
             wordlistCat(ftp.server_msg, &mb);
         }
         break;
 
     case 'h':
-        mb.Printf("%s", getMyHostname());
+        mb.appendf("%s", getMyHostname());
         break;
 
     case 'H':
         if (request) {
             if (request->hier.host[0] != '\0') // if non-empty string.
                 p = request->hier.host;
             else
-                p = request->GetHost();
+                p = request->url.host();
         } else if (!building_deny_info_url)
             p = "[unknown host]";
         break;
 
     case 'i':
-        mb.Printf("%s", src_addr.toStr(ntoabuf,MAX_IPSTRLEN));
+        mb.appendf("%s", src_addr.toStr(ntoabuf,MAX_IPSTRLEN));
         break;
 
     case 'I':
         if (request && request->hier.tcpServer != NULL)
             p = request->hier.tcpServer->remote.toStr(ntoabuf,MAX_IPSTRLEN);
         else if (!building_deny_info_url)
