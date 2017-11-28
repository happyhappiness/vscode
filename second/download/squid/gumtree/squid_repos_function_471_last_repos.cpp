time_t
HttpReply::hdrExpirationTime()
{
    /* The s-maxage and max-age directive takes priority over Expires */

    if (cache_control) {
        int maxAge = -1;
        /*
         * Conservatively handle the case when we have a max-age
         * header, but no Date for reference?
         */
        if (cache_control->hasSMaxAge(&maxAge) || cache_control->hasMaxAge(&maxAge))
            return (date >= 0) ? date + maxAge : squid_curtime;
    }

    if (Config.onoff.vary_ignore_expire &&
            header.has(Http::HdrType::VARY)) {
        const time_t d = header.getTime(Http::HdrType::DATE);
        const time_t e = header.getTime(Http::HdrType::EXPIRES);

        if (d == e)
            return -1;
    }

    if (header.has(Http::HdrType::EXPIRES)) {
        const time_t e = header.getTime(Http::HdrType::EXPIRES);
        /*
         * HTTP/1.0 says that robust implementations should consider
         * bad or malformed Expires header as equivalent to "expires
         * immediately."
         */
        return e < 0 ? squid_curtime : e;
    }

    return -1;
}