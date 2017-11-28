     case 'b':
         mb.Printf("%d", getMyPort());
         break;
 
     case 'B':
         if (building_deny_info_url) break;
-        p = request ? ftpUrlWith2f(request) : "[no URL]";
+        p = request ? Ftp::UrlWith2f(request) : "[no URL]";
         break;
 
     case 'c':
         if (building_deny_info_url) break;
         p = errorPageName(type);
         break;
 
     case 'D':
         if (!allowRecursion)
             p = "%D";  // if recursion is not allowed, do not convert
-#if USE_SSL
+#if USE_OPENSSL
         // currently only SSL error details implemented
         else if (detail) {
             detail->useRequest(request);
             const String &errDetail = detail->toString();
-            if (errDetail.defined()) {
+            if (errDetail.size() > 0) {
                 MemBuf *detail_mb  = ConvertText(errDetail.termedBuf(), false);
                 mb.append(detail_mb->content(), detail_mb->contentSize());
                 delete detail_mb;
                 do_quote = 0;
             }
         }
