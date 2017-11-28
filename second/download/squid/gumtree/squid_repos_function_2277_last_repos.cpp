void
HttpHeader::addVia(const AnyP::ProtocolVersion &ver, const HttpHeader *from)
{
    // TODO: do not add Via header for messages where Squid itself
    // generated the message (i.e., Downloader or ESI) there should be no Via header added at all.

    if (Config.onoff.via) {
        SBuf buf;
        // RFC 7230 section 5.7.1.: protocol-name is omitted when
        // the received protocol is HTTP.
        if (ver.protocol > AnyP::PROTO_NONE && ver.protocol < AnyP::PROTO_UNKNOWN &&
                ver.protocol != AnyP::PROTO_HTTP && ver.protocol != AnyP::PROTO_HTTPS)
            buf.appendf("%s/", AnyP::ProtocolType_str[ver.protocol]);
        buf.appendf("%d.%d %s", ver.major, ver.minor, ThisCache);
        const HttpHeader *hdr = from ? from : this;
        SBuf strVia = StringToSBuf(hdr->getList(Http::HdrType::VIA));
        if (!strVia.isEmpty())
            strVia.append(", ", 2);
        strVia.append(buf);
        // XXX: putStr() still suffers from String size limits
        Must(strVia.length() < String::SizeMaxXXX());
        delById(Http::HdrType::VIA);
        putStr(Http::HdrType::VIA, strVia.c_str());
    }
}