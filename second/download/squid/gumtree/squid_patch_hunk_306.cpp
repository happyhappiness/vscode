         return 1;
     }
 
     S.FreeAddrInfo(AI);
 
     l = snprintf(buf, sizeof(buf),
-                 "GET cache_object://%s/%s HTTP/1.0\r\n"
+                 "GET cache_object://%s/%s%s%s HTTP/1.0\r\n"
                  "User-Agent: cachemgr.cgi/%s\r\n"
                  "Accept: */*\r\n"
                  "%s"			/* Authentication info or nothing */
                  "\r\n",
                  req->hostname,
                  req->action,
+                 req->workers? "?workers=" : (req->processes ? "?processes=" : ""),
+                 req->workers? req->workers : (req->processes ? req->processes: ""),
                  VERSION,
                  make_auth_header(req));
     if (write(s, buf, l) < 0) {
-        debug(1) fprintf(stderr, "ERROR: (%d) writing request: '%s'\n", errno, buf);
+        fprintf(stderr,"ERROR: (%d) writing request: '%s'\n", errno, buf);
     } else {
-        debug(1) fprintf(stderr, "wrote request: '%s'\n", buf);
+        debug("wrote request: '%s'\n", buf);
     }
     return read_reply(s, req);
 }
 
 int
 main(int argc, char *argv[])
 {
     char *s;
     cachemgr_request *req;
 
     now = time(NULL);
-#ifdef _SQUID_MSWIN_
+#if _SQUID_MSWIN_
 
     Win32SockInit();
     atexit(Win32SockCleanup);
     _setmode( _fileno( stdin ), _O_BINARY );
     _setmode( _fileno( stdout ), _O_BINARY );
     _fmode = _O_BINARY;
