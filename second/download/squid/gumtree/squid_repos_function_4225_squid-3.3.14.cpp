bool Adaptation::Icap::OptXact::parseResponse()
{
    debugs(93, 5, HERE << "have " << readBuf.contentSize() << " bytes to parse" <<
           status());
    debugs(93, 5, HERE << "\n" << readBuf.content());

    HttpReply::Pointer r(new HttpReply);
    r->protoPrefix = "ICAP/"; // TODO: make an IcapReply class?

    if (!parseHttpMsg(r)) // throws on errors
        return false;

    if (httpHeaderHasConnDir(&r->header, "close"))
        reuseConnection = false;

    icapReply = r;
    return true;
}