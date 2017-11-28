bool
HttpRequestMethod::respMaybeCacheable() const
{
    // Only a few methods are defined as cacheable.
    // All other methods from the below RFC are "MUST NOT cache"
    switch (theMethod) {
        // RFC 2616 section 9
    case Http::METHOD_GET:
    case Http::METHOD_HEAD:
        return true;
#if WHEN_POST_CACHE_SUPPORTED
    case Http::METHOD_POST: // Special case.
        // RFC 2616 specifies POST as possibly cacheable
        // However, Squid does not implement the required checks yet
        return true;
#endif

        // RFC 4918 section 9
#if WHEN_PROPFIND_CACHE_SUPPORTED
    case Http::METHOD_PROPFIND: // Special case.
        // RFC 4918 specifies PROPFIND as possibly cacheable
        // However, Squid does not implement the required checks yet
        return true;
#endif

        // RFC 5323 section 2 - defines no cacheable methods

        // RFC 3253
#if WHEN_CC_NOCACHE_DOES_REVALIDATES_IS_CONFIRMED
    case Http::METHOD_CHECKOUT:
    case Http::METHOD_CHECKIN:
    case Http::METHOD_UNCHECKOUT:
    case Http::METHOD_MKWORKSPACE:
    case Http::METHOD_VERSION_CONTROL:
    case Http::METHOD_UPDATE:
    case Http::METHOD_LABEL:
    case Http::METHOD_MERGE:
    case Http::METHOD_BASELINE_CONTROL:
    case Http::METHOD_MKACTIVITY:
        // RFC 3253 defines these methods using "MUST include Cache-Control: no-cache".
        //
        // XXX: follow RFC 2616 definition of "no-cache" meaning "MAY cache, always revalidate"
        // XXX: or treat as unregistered/undefined methods ??
        // However, Squid may not implement the required revalidation checks yet
        return ??;
#endif

        // Special Squid method tokens are not cacheable.
        // RFC 2616 defines all unregistered or unspecified methods as non-cacheable
        // until such time as an RFC defines them cacheable.
    default:
        return false;
    }
}