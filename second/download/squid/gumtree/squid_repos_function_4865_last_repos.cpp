void
Http::StatusLine::packInto(Packable * p) const
{
    assert(p);

    /* local constants */
    /* AYJ: see bug 2469 - RFC2616 confirms stating 'SP characters' plural! */
    static const char *Http1StatusLineFormat = "HTTP/%d.%d %3d %s\r\n";
    static const char *IcyStatusLineFormat = "ICY %3d %s\r\n";

    /* handle ICY protocol status line specially. Pass on the bad format. */
    if (protocol == AnyP::PROTO_ICY) {
        debugs(57, 9, "packing sline " << this << " using " << p << ":");
        debugs(57, 9, "FORMAT=" << IcyStatusLineFormat );
        debugs(57, 9, "ICY " << status() << " " << reason());
        p->appendf(IcyStatusLineFormat, status(), reason());
        return;
    }

    debugs(57, 9, "packing sline " << this << " using " << p << ":");
    debugs(57, 9, "FORMAT=" << Http1StatusLineFormat );
    debugs(57, 9, "HTTP/" << version.major << "." << version.minor << " " << status() << " " << reason());
    p->appendf(Http1StatusLineFormat, version.major, version.minor, status(), reason());
}