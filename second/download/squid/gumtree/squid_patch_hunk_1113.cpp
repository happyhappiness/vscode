 #endif
 
 #include <algorithm>
 #include <cerrno>
 #include <string>
 
-static void httpHeaderPutStrvf(HttpHeader * hdr, http_hdr_type id, const char *fmt, va_list vargs);
-
-HttpHeaderFieldInfo *
-httpHeaderBuildFieldsInfo(const HttpHeaderFieldAttrs * attrs, int count)
-{
-    int i;
-    HttpHeaderFieldInfo *table = NULL;
-    assert(attrs && count);
-
-    /* allocate space */
-    table = new HttpHeaderFieldInfo[count];
-
-    for (i = 0; i < count; ++i) {
-        const http_hdr_type id = attrs[i].id;
-        HttpHeaderFieldInfo *info = table + id;
-        /* sanity checks */
-        assert(id >= 0 && id < count);
-        assert(attrs[i].name);
-        assert(info->id == HDR_ACCEPT && info->type == ftInvalid);  /* was not set before */
-        /* copy and init fields */
-        info->id = id;
-        info->type = attrs[i].type;
-        info->name = attrs[i].name;
-        assert(info->name.size());
-    }
-
-    return table;
-}
-
-void
-httpHeaderDestroyFieldsInfo(HttpHeaderFieldInfo * table, int count)
-{
-    int i;
-
-    for (i = 0; i < count; ++i)
-        table[i].name.clean();
-
-    delete [] table;
-}
+static void httpHeaderPutStrvf(HttpHeader * hdr, Http::HdrType id, const char *fmt, va_list vargs);
+static void httpHdrAdd(HttpHeader *heads, HttpRequest *request, const AccessLogEntryPointer &al, HeaderWithAclList &headersAdd);
 
 void
 httpHeaderMaskInit(HttpHeaderMask * mask, int value)
 {
     memset(mask, value, sizeof(*mask));
 }
 
-/** calculates a bit mask of a given array; does not reset mask! */
-void
-httpHeaderCalcMask(HttpHeaderMask * mask, http_hdr_type http_hdr_type_enums[], size_t count)
-{
-    size_t i;
-    const int * enums = (const int *) http_hdr_type_enums;
-    assert(mask && enums);
-    assert(count < sizeof(*mask) * 8);  /* check for overflow */
-
-    for (i = 0; i < count; ++i) {
-        assert(!CBIT_TEST(*mask, enums[i]));    /* check for duplicates */
-        CBIT_SET(*mask, enums[i]);
-    }
-}
-
 /* same as httpHeaderPutStr, but formats the string using snprintf first */
 void
-httpHeaderPutStrf(HttpHeader * hdr, http_hdr_type id, const char *fmt,...)
+httpHeaderPutStrf(HttpHeader * hdr, Http::HdrType id, const char *fmt,...)
 {
     va_list args;
     va_start(args, fmt);
 
     httpHeaderPutStrvf(hdr, id, fmt, args);
     va_end(args);
 }
 
 /* used by httpHeaderPutStrf */
 static void
-httpHeaderPutStrvf(HttpHeader * hdr, http_hdr_type id, const char *fmt, va_list vargs)
+httpHeaderPutStrvf(HttpHeader * hdr, Http::HdrType id, const char *fmt, va_list vargs)
 {
     MemBuf mb;
     mb.init();
-    mb.vPrintf(fmt, vargs);
+    mb.vappendf(fmt, vargs);
     hdr->putStr(id, mb.buf);
     mb.clean();
 }
 
 /** wrapper arrounf PutContRange */
 void
 httpHeaderAddContRange(HttpHeader * hdr, HttpHdrRangeSpec spec, int64_t ent_len)
 {
     HttpHdrContRange *cr = httpHdrContRangeCreate();
     assert(hdr && ent_len >= 0);
     httpHdrContRangeSet(cr, spec, ent_len);
     hdr->putContRange(cr);
-    httpHdrContRangeDestroy(cr);
+    delete cr;
 }
 
 /**
  * \return true if a given directive is found in the Connection header field-value.
  *
  * \note if no Connection header exists we may check the Proxy-Connection header
