 
             if (request->urlpath.size() != 0)
                 urlpath_or_slash = request->urlpath;
             else
                 urlpath_or_slash = "/";
 
-            mb.Printf("%s " SQUIDSTRINGPH " %s/%d.%d\n",
-                      RequestMethodStr(request->method),
+            mb.Printf(SQUIDSBUFPH " " SQUIDSTRINGPH " %s/%d.%d\n",
+                      SQUIDSBUFPRINT(request->method.image()),
                       SQUIDSTRINGPRINT(urlpath_or_slash),
                       AnyP::ProtocolType_str[request->http_ver.protocol],
                       request->http_ver.major, request->http_ver.minor);
             packerToMemInit(&pck, &mb);
             request->header.packInto(&pck, true); //hide authorization data
             packerClean(&pck);
