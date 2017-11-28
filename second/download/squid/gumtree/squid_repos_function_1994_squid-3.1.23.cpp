int
HttpStateData::cacheableReply()
{
    HttpReply const *rep = finalReply();
    HttpHeader const *hdr = &rep->header;
    const int cc_mask = (rep->cache_control) ? rep->cache_control->mask : 0;
    const char *v;
#if HTTP_VIOLATIONS

    const refresh_t *R = NULL;

    /* This strange looking define first looks up the refresh pattern
     * and then checks if the specified flag is set. The main purpose
     * of this is to simplify the refresh pattern lookup and HTTP_VIOLATIONS
     * condition
     */
#define REFRESH_OVERRIDE(flag) \
    ((R = (R ? R : refreshLimits(entry->mem_obj->url))) , \
    (R && R->flags.flag))
#else
#define REFRESH_OVERRIDE(flag) 0
#endif

    if (surrogateNoStore)
        return 0;

    // RFC 2616: do not cache replies to responses with no-store CC directive
    if (request && request->cache_control &&
            EBIT_TEST(request->cache_control->mask, CC_NO_STORE) &&
            !REFRESH_OVERRIDE(ignore_no_store))
        return 0;

    if (!ignoreCacheControl) {
        if (EBIT_TEST(cc_mask, CC_PRIVATE)) {
            if (!REFRESH_OVERRIDE(ignore_private))
                return 0;
        }

        if (EBIT_TEST(cc_mask, CC_NO_CACHE)) {
            if (!REFRESH_OVERRIDE(ignore_no_cache))
                return 0;
        }

        if (EBIT_TEST(cc_mask, CC_NO_STORE)) {
            if (!REFRESH_OVERRIDE(ignore_no_store))
                return 0;
        }
    }

    if (request->flags.auth || request->flags.auth_sent) {
        /*
         * Responses to requests with authorization may be cached
         * only if a Cache-Control: public reply header is present.
         * RFC 2068, sec 14.9.4
         */

        if (!EBIT_TEST(cc_mask, CC_PUBLIC)) {
            if (!REFRESH_OVERRIDE(ignore_auth))
                return 0;
        }
    }

    /* Pragma: no-cache in _replies_ is not documented in HTTP,
     * but servers like "Active Imaging Webcast/2.0" sure do use it */
    if (hdr->has(HDR_PRAGMA)) {
        String s = hdr->getList(HDR_PRAGMA);
        const int no_cache = strListIsMember(&s, "no-cache", ',');
        s.clean();

        if (no_cache) {
            if (!REFRESH_OVERRIDE(ignore_no_cache))
                return 0;
        }
    }

    /*
     * The "multipart/x-mixed-replace" content type is used for
     * continuous push replies.  These are generally dynamic and
     * probably should not be cachable
     */
    if ((v = hdr->getStr(HDR_CONTENT_TYPE)))
        if (!strncasecmp(v, "multipart/x-mixed-replace", 25))
            return 0;

    switch (rep->sline.status) {
        /* Responses that are cacheable */

    case HTTP_OK:

    case HTTP_NON_AUTHORITATIVE_INFORMATION:

    case HTTP_MULTIPLE_CHOICES:

    case HTTP_MOVED_PERMANENTLY:

    case HTTP_GONE:
        /*
         * Don't cache objects that need to be refreshed on next request,
         * unless we know how to refresh it.
         */

        if (!refreshIsCachable(entry)) {
            debugs(22, 3, "refreshIsCachable() returned non-cacheable..");
            return 0;
        } else
            return 1;

        /* NOTREACHED */
        break;

        /* Responses that only are cacheable if the server says so */

    case HTTP_MOVED_TEMPORARILY:
    case HTTP_TEMPORARY_REDIRECT:
        if (rep->expires > rep->date && rep->date > 0)
            return 1;
        else
            return 0;

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

        return 0;

    default:
        /* RFC 2616 section 6.1.1: an unrecognized response MUST NOT be cached. */
        debugs (11, 3, HERE << "Unknown HTTP status code " << rep->sline.status << ". Not cacheable.");

        return 0;

        /* NOTREACHED */
        break;
    }

    /* NOTREACHED */
}