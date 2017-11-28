static const HttpMsg *
actualRequestHeader(const AccessLogEntry::Pointer &al)
{
#if ICAP_CLIENT
    // al->icap.reqMethod is methodNone in access.log context
    if (al->icap.reqMethod == Adaptation::methodRespmod) {
        // XXX: for now AccessLogEntry lacks virgin response headers
        return NULL;
    }
#endif
    return al->request;
}