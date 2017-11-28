}

void Adaptation::Icap::OptXact::makeRequest(MemBuf &buf)
{
    const Adaptation::Service &s = service();
    const String uri = s.cfg().uri;
    buf.Printf("OPTIONS " SQUIDSTRINGPH " ICAP/1.0\r\n", SQUIDSTRINGPRINT(uri));
    const String host = s.cfg().host;
    buf.Printf("Host: " SQUIDSTRINGPH ":%d\r\n", SQUIDSTRINGPRINT(host), s.cfg().port);

    if (!TheConfig.reuse_connections)
        buf.Printf("Connection: close\r\n");

    if (TheConfig.allow206_enable)
        buf.Printf("Allow: 206\r\n");
    buf.append(ICAP::crlf, 2);

    // XXX: HttpRequest cannot fully parse ICAP Request-Line
    Http::StatusCode reqStatus;
    Must(icapRequest->parse(&buf, true, &reqStatus) > 0);
}

void Adaptation::Icap::OptXact::handleCommWrote(size_t size)
{
    debugs(93, 9, HERE << "finished writing " << size <<
           "-byte request " << status());
