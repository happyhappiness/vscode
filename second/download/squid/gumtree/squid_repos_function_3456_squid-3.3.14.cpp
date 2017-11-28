int
httpStatusLineParse(HttpStatusLine * sline, const String &protoPrefix, const char *start, const char *end)
{
    assert(sline);
    sline->status = HTTP_INVALID_HEADER;	/* Squid header parsing error */

    // XXX: HttpMsg::parse() has a similar check but is using
    // casesensitive comparison (which is required by HTTP errata?)

    if (protoPrefix.cmp("ICY", 3) == 0) {
        debugs(57, 3, "httpStatusLineParse: Invalid HTTP identifier. Detected ICY protocol istead.");
        sline->protocol = AnyP::PROTO_ICY;
        start += protoPrefix.size();
    } else if (protoPrefix.caseCmp(start, protoPrefix.size()) == 0) {

        start += protoPrefix.size();

        if (!xisdigit(*start))
            return 0;

        if (sscanf(start, "%d.%d", &sline->version.major, &sline->version.minor) != 2) {
            debugs(57, 7, "httpStatusLineParse: Invalid HTTP identifier.");
        }
    } else
        return 0;

    if (!(start = strchr(start, ' ')))
        return 0;

    sline->status = (http_status) atoi(++start);

    /* we ignore 'reason-phrase' */
    /* Should assert start < end ? */
    return 1;			/* success */
}