 }
 
 void
 HttpReply::redirect(http_status status, const char *loc)
 {
     HttpHeader *hdr;
-    HttpVersion ver(1,0);
+    HttpVersion ver(1,1);
     httpStatusLineSet(&sline, ver, status, httpStatusString(status));
     hdr = &header;
     hdr->putStr(HDR_SERVER, APP_FULLNAME);
     hdr->putTime(HDR_DATE, squid_curtime);
     hdr->putInt64(HDR_CONTENT_LENGTH, 0);
     hdr->putStr(HDR_LOCATION, loc);
