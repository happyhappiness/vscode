void Adaptation::Icap::History::assign(const Adaptation::Icap::History& ih)
{
    mergeOfIcapHeaders.clean();
    mergeOfIcapHeaders.update(&ih.mergeOfIcapHeaders, NULL);
    lastIcapHeader.clean();
    lastIcapHeader.update(&ih.lastIcapHeader, NULL);
    rfc931 = ih.rfc931;

#if USE_SSL
    ssluser = ih.ssluser;
#endif

    logType = ih.logType;
    log_uri = ih.log_uri;
    req_sz = ih.req_sz;
    pastTime = ih.pastTime;
    currentStart = ih.currentStart;
    concurrencyLevel = ih.concurrencyLevel;
    debugs(93,7, HERE << this << " = " << &ih);
}