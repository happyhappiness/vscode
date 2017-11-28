void
accessLogFreeMemory(AccessLogEntry * aLogEntry)
{
    safe_free(aLogEntry->headers.request);

#if ICAP_CLIENT
    safe_free(aLogEntry->headers.icap);
#endif

    safe_free(aLogEntry->headers.reply);
    safe_free(aLogEntry->cache.authuser);

    safe_free(aLogEntry->headers.adapted_request);
    HTTPMSGUNLOCK(aLogEntry->adapted_request);

    HTTPMSGUNLOCK(aLogEntry->reply);
    HTTPMSGUNLOCK(aLogEntry->request);
#if ICAP_CLIENT
    HTTPMSGUNLOCK(aLogEntry->icap.reply);
    HTTPMSGUNLOCK(aLogEntry->icap.request);
#endif
}