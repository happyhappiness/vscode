                  ThisCache);
         strListAdd(&strVia, bbuf, ',');
         hdr->delById(HDR_VIA);
         hdr->putStr(HDR_VIA, strVia.termedBuf());
     }
     /* Signal keep-alive or close explicitly */
-    hdr->putStr(HDR_CONNECTION, request->flags.proxy_keepalive ? "keep-alive" : "close");
+    hdr->putStr(HDR_CONNECTION, request->flags.proxyKeepalive ? "keep-alive" : "close");
 
 #if ADD_X_REQUEST_URI
     /*
      * Knowing the URI of the request is useful when debugging persistent
      * connections in a client; we cannot guarantee the order of http headers,
      * but X-Request-URI is likely to be the very last header to ease use from a
