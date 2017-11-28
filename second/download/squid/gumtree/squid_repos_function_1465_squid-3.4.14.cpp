bool
HttpRequestMethod::isHttpSafe() const
{
    // Only a few methods are defined as safe. All others are "unsafe"

    // NOTE:
    // All known RFCs which register methods are listed in comments.
    // if there is one not listed which defines methods, it needs
    // checking and adding. If only to say it is known to define none.

    switch (theMethod) {
        // RFC 2068 - none

        // RFC 2616 section 9.1.1
    case Http::METHOD_GET:
    case Http::METHOD_HEAD:
    case Http::METHOD_OPTIONS:

        // RFC 3253 section 3.6
    case Http::METHOD_REPORT:

        // RFC 3648 - none
        // RFC 3744 - none
        // RFC 4437 - none
        // RFC 4791 - none

        // RFC 4918 section 9.1
    case Http::METHOD_PROPFIND:

        // RFC 5323 section 2
    case Http::METHOD_SEARCH:

        // RFC 5789 - none
        // RFC 5842 - none

        return true;

    default:
        return false;
    }
}