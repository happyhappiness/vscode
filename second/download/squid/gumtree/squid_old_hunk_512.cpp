
    if (TheConfig.allow206_enable)
        buf.Printf("Allow: 206\r\n");
    buf.append(ICAP::crlf, 2);

    // XXX: HttpRequest cannot fully parse ICAP Request-Line
    http_status reqStatus;
    Must(icapRequest->parse(&buf, true, &reqStatus) > 0);
}

void Adaptation::Icap::OptXact::handleCommWrote(size_t size)
{
    debugs(93, 9, HERE << "finished writing " << size <<
