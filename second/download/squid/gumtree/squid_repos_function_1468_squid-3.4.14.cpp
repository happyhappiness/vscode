bool
HttpRequestMethod::shouldInvalidate() const
{
    switch (theMethod) {
        /* RFC 2616 section 13.10 - "MUST invalidate" */
    case Http::METHOD_POST:
    case Http::METHOD_PUT:
    case Http::METHOD_DELETE:
        return true;

        /* Squid extension to force invalidation */
    case Http::METHOD_PURGE:
        return true;

        /*
         * RFC 2616 sayeth, in section 13.10, final paragraph:
         * A cache that passes through requests for methods it does not
         * understand SHOULD invalidate any entities referred to by the
         * Request-URI.
         */
    case Http::METHOD_OTHER:
        return true;

    default:
        // Methods which are known but not required to invalidate.
        return false;
    }
}