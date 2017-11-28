 
 HttpHeaderFieldInfo *httpHeaderBuildFieldsInfo(const HttpHeaderFieldAttrs * attrs, int count);
 void httpHeaderDestroyFieldsInfo(HttpHeaderFieldInfo * info, int count);
 http_hdr_type httpHeaderIdByName(const char *name, size_t name_len, const HttpHeaderFieldInfo * attrs, int end);
 http_hdr_type httpHeaderIdByNameDef(const char *name, int name_len);
 const char *httpHeaderNameById(int id);
-int httpHeaderHasConnDir(const HttpHeader * hdr, const char *directive);
+bool httpHeaderHasConnDir(const HttpHeader * hdr, const char *directive);
 int httpHeaderParseInt(const char *start, int *val);
 void httpHeaderPutStrf(HttpHeader * hdr, http_hdr_type id, const char *fmt,...) PRINTF_FORMAT_ARG3;
 
 const char *getStringPrefix(const char *str, const char *end);
 
 void httpHdrMangleList(HttpHeader *, HttpRequest *, int req_or_rep);
