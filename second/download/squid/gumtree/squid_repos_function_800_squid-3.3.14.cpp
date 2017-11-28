time_t
HttpReply::hdrExpirationTime()
{
    /* The s-maxage and max-age directive takes priority over Expires */

    if (cache_control) {
        if (date >= 0) {
            if (cache_control->hasSMaxAge())
                return date + cache_control->sMaxAge();

            if (cache_control->hasMaxAge())
                return date + cache_control->maxAge();
        } else {
            /*
             * Conservatively handle the case when we have a max-age
             * header, but no Date for reference?
             */

            if (cache_control->hasSMaxAge())
                return squid_curtime;

            if (cache_control->hasMaxAge())
                return squid_curtime;
        }
    }

    if (Config.onoff.vary_ignore_expire &&
            header.has(HDR_VARY)) {
        const time_t d = header.getTime(HDR_DATE);
        const time_t e = header.getTime(HDR_EXPIRES);

        if (d == e)
            return -1;
    }

    if (header.has(HDR_EXPIRES)) {
        const time_t e = header.getTime(HDR_EXPIRES);
        /*
         * HTTP/1.0 says that robust implementations should consider
         * bad or malformed Expires header as equivalent to "expires
         * immediately."
         */
        return e < 0 ? squid_curtime : e;
    }

    return -1;
}