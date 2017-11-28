void Adaptation::Icap::ModXact::parseHttpHead()
{
    if (gotEncapsulated("res-hdr") || gotEncapsulated("req-hdr")) {
        maybeAllocateHttpMsg();

        if (!parseHead(adapted.header))
            return; // need more header data

        if (dynamic_cast<HttpRequest*>(adapted.header)) {
            const HttpRequest *oldR = dynamic_cast<const HttpRequest*>(virgin.header);
            Must(oldR);
            // TODO: the adapted request did not really originate from the
            // client; give proxy admin an option to prevent copying of
            // sensitive client information here. See the following thread:
            // http://www.squid-cache.org/mail-archive/squid-dev/200703/0040.html
        }

        // Maybe adapted.header==NULL if HttpReply and have Http 0.9 ....
        if (adapted.header)
            adapted.header->inheritProperties(virgin.header);
    }

    decideOnParsingBody();
}