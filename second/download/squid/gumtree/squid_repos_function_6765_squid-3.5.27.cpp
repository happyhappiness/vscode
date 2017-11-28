static const HttpMsg *
actualReplyHeader(const AccessLogEntry::Pointer &al)
{
    const HttpMsg *msg = al->reply;
#if ICAP_CLIENT
    // al->icap.reqMethod is methodNone in access.log context
    if (!msg && al->icap.reqMethod == Adaptation::methodReqmod)
        msg = al->adapted_request;
#endif
    return msg;
}