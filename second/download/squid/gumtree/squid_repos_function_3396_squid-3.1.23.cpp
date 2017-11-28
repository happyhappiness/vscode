void
httpStatusLinePackInto(const HttpStatusLine * sline, Packer * p)
{
    assert(sline && p);

    /* handle ICY protocol status line specially. Pass on the bad format. */
    if (sline->protocol == PROTO_ICY) {
        debugs(57, 9, "packing sline " << sline << " using " << p << ":");
        debugs(57, 9, "FORMAT=" << IcyStatusLineFormat );
        debugs(57, 9, "ICY " << sline->status << " " << (sline->reason ? sline->reason : httpStatusString(sline->status)) );
        packerPrintf(p, IcyStatusLineFormat, sline->status, httpStatusLineReason(sline));
        return;
    }

    debugs(57, 9, "packing sline " << sline << " using " << p << ":");
    debug(57, 9) (HttpStatusLineFormat, sline->version.major,
                  sline->version.minor, sline->status,
                  sline->reason ? sline->reason : httpStatusString(sline->status));
    packerPrintf(p, HttpStatusLineFormat, sline->version.major,
                 sline->version.minor, sline->status, httpStatusLineReason(sline));
}