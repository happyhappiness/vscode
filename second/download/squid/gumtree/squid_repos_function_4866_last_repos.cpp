bool
Http::StatusLine::parse(const String &protoPrefix, const char *start, const char * /*end*/)
{
    status_ = Http::scInvalidHeader;    /* Squid header parsing error */

    // XXX: HttpMsg::parse() has a similar check but is using
    // casesensitive comparison (which is required by HTTP errata?)

    if (protoPrefix.cmp("ICY", 3) == 0) {
        debugs(57, 3, "Invalid HTTP identifier. Detected ICY protocol istead.");
        protocol = AnyP::PROTO_ICY;
        start += protoPrefix.size();
    } else if (protoPrefix.caseCmp(start, protoPrefix.size()) == 0) {

        start += protoPrefix.size();

        if (!xisdigit(*start))
            return false;

        // XXX: HTTPbis have defined this to be single-digit version numbers. no need to sscanf()
        // XXX: furthermore, only HTTP/1 will be using ASCII format digits

        if (sscanf(start, "%d.%d", &version.major, &version.minor) != 2) {
            debugs(57, 7, "Invalid HTTP identifier.");
            return false;
        }
    } else
        return false;

    if (!(start = strchr(start, ' ')))
        return false;

    // XXX: should we be using xstrtoui() or xatoui() ?
    status_ = static_cast<Http::StatusCode>(atoi(++start));

    // XXX check if the given 'reason' is the default status string, if not save to reason_

    /* we ignore 'reason-phrase' */
    /* Should assert start < end ? */
    return true;            /* success */
}