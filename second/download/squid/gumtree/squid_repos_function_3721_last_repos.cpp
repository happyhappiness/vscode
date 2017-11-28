bool Adaptation::Icap::OptXact::parseResponse()
{
    debugs(93, 5, "have " << readBuf.length() << " bytes to parse" << status());
    debugs(93, DBG_DATA, "\n" << readBuf);

    HttpReply::Pointer r(new HttpReply);
    r->protoPrefix = "ICAP/"; // TODO: make an IcapReply class?

    if (!parseHttpMsg(r.getRaw())) // throws on errors
        return false;

    if (httpHeaderHasConnDir(&r->header, "close"))
        reuseConnection = false;

    icapReply = r;
    return true;
}