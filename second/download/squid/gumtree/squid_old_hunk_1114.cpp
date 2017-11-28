    ACLList *aclList;

    /// compiled HTTP header field value (no macros)
    Format::Format *valueFormat;

    /// internal ID for "known" headers or HDR_OTHER
    http_hdr_type fieldId;

    /// whether fieldValue may contain macros
    bool quoted;
};

int httpHeaderParseOffset(const char *start, int64_t * off);

HttpHeaderFieldInfo *httpHeaderBuildFieldsInfo(const HttpHeaderFieldAttrs * attrs, int count);
void httpHeaderDestroyFieldsInfo(HttpHeaderFieldInfo * info, int count);
http_hdr_type httpHeaderIdByName(const char *name, size_t name_len, const HttpHeaderFieldInfo * attrs, int end);
http_hdr_type httpHeaderIdByNameDef(const char *name, int name_len);
const char *httpHeaderNameById(int id);
bool httpHeaderHasConnDir(const HttpHeader * hdr, const char *directive);
int httpHeaderParseInt(const char *start, int *val);
void httpHeaderPutStrf(HttpHeader * hdr, http_hdr_type id, const char *fmt,...) PRINTF_FORMAT_ARG3;

const char *getStringPrefix(const char *str, const char *end);

void httpHdrMangleList(HttpHeader *, HttpRequest *, int req_or_rep);

#endif

