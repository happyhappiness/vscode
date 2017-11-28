#endif

#include <algorithm>
#include <cerrno>
#include <string>

static void httpHeaderPutStrvf(HttpHeader * hdr, Http::HdrType id, const char *fmt, va_list vargs);
static void httpHdrAdd(HttpHeader *heads, HttpRequest *request, const AccessLogEntryPointer &al, HeaderWithAclList &headersAdd);

void
httpHeaderMaskInit(HttpHeaderMask * mask, int value)
{
    memset(mask, value, sizeof(*mask));
}

/* same as httpHeaderPutStr, but formats the string using snprintf first */
void
httpHeaderPutStrf(HttpHeader * hdr, Http::HdrType id, const char *fmt,...)
{
    va_list args;
    va_start(args, fmt);

    httpHeaderPutStrvf(hdr, id, fmt, args);
    va_end(args);
}

/* used by httpHeaderPutStrf */
static void
httpHeaderPutStrvf(HttpHeader * hdr, Http::HdrType id, const char *fmt, va_list vargs)
{
    MemBuf mb;
    mb.init();
    mb.vappendf(fmt, vargs);
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
    delete cr;
}

/**
 * \return true if a given directive is found in the Connection header field-value.
 *
 * \note if no Connection header exists we may check the Proxy-Connection header
