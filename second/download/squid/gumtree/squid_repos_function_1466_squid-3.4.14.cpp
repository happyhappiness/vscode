bool
HttpRequestMethod::isIdempotent() const
{
    // Only a few methods are defined as idempotent.

    // NOTE:
    // All known RFCs which register methods are listed in comments.
    // if there is one not listed which defines methods, it needs
    // checking and adding. If only to say it is known to define none.

    switch (theMethod) {
        // RFC 2068 - TODO check LINK/UNLINK definition

        // RFC 2616 section 9.1.2
    case Http::METHOD_GET:
    case Http::METHOD_HEAD:
    case Http::METHOD_PUT:
    case Http::METHOD_DELETE:
    case Http::METHOD_OPTIONS:
    case Http::METHOD_TRACE:

        // RFC 3253 - TODO check
        // RFC 3648 - TODO check
        // RFC 3744 - TODO check
        // RFC 4437 - TODO check
        // RFC 4791 - TODO check

        // RFC 4918 section 9
    case Http::METHOD_PROPFIND:
    case Http::METHOD_PROPPATCH:
    case Http::METHOD_MKCOL:
    case Http::METHOD_COPY:
    case Http::METHOD_MOVE:
    case Http::METHOD_UNLOCK:

        // RFC 5323 - TODO check
        // RFC 5789 - TODO check
        // RFC 5842 - TODO check

        return true;

    default:
        return false;
    }
}