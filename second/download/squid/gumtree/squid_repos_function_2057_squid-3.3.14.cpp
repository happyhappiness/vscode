int
HttpStateData::cacheableReply()
{
    HttpReply const *rep = finalReply();
    HttpHeader const *hdr = &rep->header;
    const char *v;
#if USE_HTTP_VIOLATIONS

    const RefreshPattern *R = NULL;

    /* This strange looking define first looks up the refresh pattern
     * and then checks if the specified flag is set. The main purpose
     * of this is to simplify the refresh pattern lookup and USE_HTTP_VIOLATIONS
     * condition
     */
#define REFRESH_OVERRIDE(flag) \
    ((R = (R ? R : refreshLimits(entry->mem_obj->url))) , \
    (R && R->flags.flag))
#else
#define REFRESH_OVERRIDE(flag) 0
#endif

    // Check for Surrogate/1.0 protocol conditions
    // NP: reverse-proxy traffic our parent server has instructed us never to cache
    if (surrogateNoStore) {
        debugs(22, 3, HERE << "NO because Surrogate-Control:no-store");
        return 0;
    }

    // RFC 2616: HTTP/1.1 Cache-Control conditions
    if (!ignoreCacheControl) {
        // XXX: check to see if the request headers alone were enough to prevent caching earlier
        // (ie no-store request header) no need to check those all again here if so.
        // for now we are not reliably doing that so we waste CPU re-checking request CC

        // RFC 2616 section 14.9.2 - MUST NOT cache any response with request CC:no-store
        if (request && request->cache_control && request->cache_control->noStore() &&
                !REFRESH_OVERRIDE(ignore_no_store)) {
            debugs(22, 3, HERE << "NO because client request Cache-Control:no-store");
            return 0;
        }

        // NP: request CC:no-cache only means cache READ is forbidden. STORE is permitted.
        if (rep->cache_control && rep->cache_control->hasNoCache() && rep->cache_control->noCache().defined()) {
            /* TODO: we are allowed to cache when no-cache= has parameters.
             * Provided we strip away any of the listed headers unless they are revalidated
             * successfully (ie, must revalidate AND these headers are prohibited on stale replies).
             * That is a bit tricky for squid right now so we avoid caching entirely.
             */
            debugs(22, 3, HERE << "NO because server reply Cache-Control:no-cache has parameters");
            return 0;
        }

        // NP: request CC:private is undefined. We ignore.
        // NP: other request CC flags are limiters on HIT/MISS. We don't care about here.

        // RFC 2616 section 14.9.2 - MUST NOT cache any response with CC:no-store
        if (rep->cache_control && rep->cache_control->noStore() &&
                !REFRESH_OVERRIDE(ignore_no_store)) {
            debugs(22, 3, HERE << "NO because server reply Cache-Control:no-store");
            return 0;
        }

        // RFC 2616 section 14.9.1 - MUST NOT cache any response with CC:private in a shared cache like Squid.
        // CC:private overrides CC:public when both are present in a response.
        // TODO: add a shared/private cache configuration possibility.
        if (rep->cache_control &&
                rep->cache_control->hasPrivate() &&
                !REFRESH_OVERRIDE(ignore_private)) {
            /* TODO: we are allowed to cache when private= has parameters.
             * Provided we strip away any of the listed headers unless they are revalidated
             * successfully (ie, must revalidate AND these headers are prohibited on stale replies).
             * That is a bit tricky for squid right now so we avoid caching entirely.
             */
            debugs(22, 3, HERE << "NO because server reply Cache-Control:private");
            return 0;
        }
    }

    // RFC 2068, sec 14.9.4 - MUST NOT cache any response with Authentication UNLESS certain CC controls are present
    // allow HTTP violations to IGNORE those controls (ie re-block caching Auth)
    if (request && (request->flags.auth || request->flags.authSent) && !REFRESH_OVERRIDE(ignore_auth)) {
        if (!rep->cache_control) {
            debugs(22, 3, HERE << "NO because Authenticated and server reply missing Cache-Control");
            return 0;
        }

        if (ignoreCacheControl) {
            debugs(22, 3, HERE << "NO because Authenticated and ignoring Cache-Control");
            return 0;
        }

        bool mayStore = false;
        // HTTPbis pt6 section 3.2: a response CC:public is present
        if (rep->cache_control->Public()) {
            debugs(22, 3, HERE << "Authenticated but server reply Cache-Control:public");
            mayStore = true;

            // HTTPbis pt6 section 3.2: a response CC:must-revalidate is present
        } else if (rep->cache_control->mustRevalidate() && !REFRESH_OVERRIDE(ignore_must_revalidate)) {
            debugs(22, 3, HERE << "Authenticated but server reply Cache-Control:public");
            mayStore = true;

#if USE_HTTP_VIOLATIONS
            // NP: given the must-revalidate exception we should also be able to exempt no-cache.
            // HTTPbis WG verdict on this is that it is omitted from the spec due to being 'unexpected' by
            // some. The caching+revalidate is not exactly unsafe though with Squids interpretation of no-cache
            // (without parameters) as equivalent to must-revalidate in the reply.
        } else if (rep->cache_control->hasNoCache() && !rep->cache_control->noCache().defined() && !REFRESH_OVERRIDE(ignore_must_revalidate)) {
            debugs(22, 3, HERE << "Authenticated but server reply Cache-Control:no-cache (equivalent to must-revalidate)");
            mayStore = true;
#endif

            // HTTPbis pt6 section 3.2: a response CC:s-maxage is present
        } else if (rep->cache_control->sMaxAge()) {
            debugs(22, 3, HERE << "Authenticated but server reply Cache-Control:s-maxage");
            mayStore = true;
        }

        if (!mayStore) {
            debugs(22, 3, HERE << "NO because Authenticated transaction");
            return 0;
        }

        // NP: response CC:no-cache is equivalent to CC:must-revalidate,max-age=0. We MAY cache, and do so.
        // NP: other request CC flags are limiters on HIT/MISS/REFRESH. We don't care about here.
    }

    /* HACK: The "multipart/x-mixed-replace" content type is used for
     * continuous push replies.  These are generally dynamic and
     * probably should not be cachable
     */
    if ((v = hdr->getStr(HDR_CONTENT_TYPE)))
        if (!strncasecmp(v, "multipart/x-mixed-replace", 25)) {
            debugs(22, 3, HERE << "NO because Content-Type:multipart/x-mixed-replace");
            return 0;
        }

    switch (rep->sline.status) {
        /* Responses that are cacheable */

    case HTTP_OK:

    case HTTP_NON_AUTHORITATIVE_INFORMATION:

    case HTTP_MULTIPLE_CHOICES:

    case HTTP_MOVED_PERMANENTLY:
    case HTTP_PERMANENT_REDIRECT:

    case HTTP_GONE:
        /*
         * Don't cache objects that need to be refreshed on next request,
         * unless we know how to refresh it.
         */

        if (!refreshIsCachable(entry) && !REFRESH_OVERRIDE(store_stale)) {
            debugs(22, 3, "NO because refreshIsCachable() returned non-cacheable..");
            return 0;
        } else {
            debugs(22, 3, HERE << "YES because HTTP status " << rep->sline.status);
            return 1;
        }
        /* NOTREACHED */
        break;

        /* Responses that only are cacheable if the server says so */

    case HTTP_MOVED_TEMPORARILY:
    case HTTP_TEMPORARY_REDIRECT:
        if (rep->date <= 0) {
            debugs(22, 3, HERE << "NO because HTTP status " << rep->sline.status << " and Date missing/invalid");
            return 0;
        }
        if (rep->expires > rep->date) {
            debugs(22, 3, HERE << "YES because HTTP status " << rep->sline.status << " and Expires > Date");
            return 1;
        } else {
            debugs(22, 3, HERE << "NO because HTTP status " << rep->sline.status << " and Expires <= Date");
            return 0;
        }
        /* NOTREACHED */
        break;

        /* Errors can be negatively cached */

    case HTTP_NO_CONTENT:

    case HTTP_USE_PROXY:

    case HTTP_BAD_REQUEST:

    case HTTP_FORBIDDEN:

    case HTTP_NOT_FOUND:

    case HTTP_METHOD_NOT_ALLOWED:

    case HTTP_REQUEST_URI_TOO_LARGE:

    case HTTP_INTERNAL_SERVER_ERROR:

    case HTTP_NOT_IMPLEMENTED:

    case HTTP_BAD_GATEWAY:

    case HTTP_SERVICE_UNAVAILABLE:

    case HTTP_GATEWAY_TIMEOUT:
        debugs(22, 3, HERE << "MAYBE because HTTP status " << rep->sline.status);
        return -1;

        /* NOTREACHED */
        break;

        /* Some responses can never be cached */

    case HTTP_PARTIAL_CONTENT:	/* Not yet supported */

    case HTTP_SEE_OTHER:

    case HTTP_NOT_MODIFIED:

    case HTTP_UNAUTHORIZED:

    case HTTP_PROXY_AUTHENTICATION_REQUIRED:

    case HTTP_INVALID_HEADER:	/* Squid header parsing error */

    case HTTP_HEADER_TOO_LARGE:

    case HTTP_PAYMENT_REQUIRED:
    case HTTP_NOT_ACCEPTABLE:
    case HTTP_REQUEST_TIMEOUT:
    case HTTP_CONFLICT:
    case HTTP_LENGTH_REQUIRED:
    case HTTP_PRECONDITION_FAILED:
    case HTTP_REQUEST_ENTITY_TOO_LARGE:
    case HTTP_UNSUPPORTED_MEDIA_TYPE:
    case HTTP_UNPROCESSABLE_ENTITY:
    case HTTP_LOCKED:
    case HTTP_FAILED_DEPENDENCY:
    case HTTP_INSUFFICIENT_STORAGE:
    case HTTP_REQUESTED_RANGE_NOT_SATISFIABLE:
    case HTTP_EXPECTATION_FAILED:

        debugs(22, 3, HERE << "NO because HTTP status " << rep->sline.status);
        return 0;

    default:
        /* RFC 2616 section 6.1.1: an unrecognized response MUST NOT be cached. */
        debugs (11, 3, HERE << "NO because unknown HTTP status code " << rep->sline.status);
        return 0;

        /* NOTREACHED */
        break;
    }

    /* NOTREACHED */
}