     expires = expiresTime;
 
     last_modified = lmt;
 }
 
 void
-HttpReply::redirect(http_status status, const char *loc)
+HttpReply::redirect(Http::StatusCode status, const char *loc)
 {
     HttpHeader *hdr;
-    HttpVersion ver(1,1);
-    httpStatusLineSet(&sline, ver, status, httpStatusString(status));
+    sline.set(Http::ProtocolVersion(1,1), status, NULL);
     hdr = &header;
     hdr->putStr(HDR_SERVER, APP_FULLNAME);
     hdr->putTime(HDR_DATE, squid_curtime);
     hdr->putInt64(HDR_CONTENT_LENGTH, 0);
     hdr->putStr(HDR_LOCATION, loc);
     date = squid_curtime;
