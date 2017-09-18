     * They are tested here one by one to be clear and unambiguous. 
     */

    /* RFC2616 13.4 we are allowed to cache 200, 203, 206, 300, 301 or 410
     * We don't cache 206, because we don't (yet) cache partial responses.
     * We include 304 Not Modified here too as this is the origin server
     * telling us to serve the cached copy.
     */
    if ((r->status != HTTP_OK && r->status != HTTP_NON_AUTHORITATIVE
         && r->status != HTTP_MULTIPLE_CHOICES
         && r->status != HTTP_MOVED_PERMANENTLY
         && r->status != HTTP_NOT_MODIFIED)
        /* if a broken Expires header is present, don't cache it */
        || (exps != NULL && exp == APR_DATE_BAD)
        /* if the server said 304 Not Modified but we have no cache
         * file - pass this untouched to the user agent, it's not for us.
         */
        || (r->status == HTTP_NOT_MODIFIED && (NULL == cache->handle))
        /* 200 OK response from HTTP/1.0 and up without a Last-Modified
         * header/Etag 
         */
        /* XXX mod-include clears last_modified/expires/etags - this
         * is why we have an optional function for a key-gen ;-) 
         */
        || (r->status == HTTP_OK && lastmods == NULL && etag == NULL 
            && (conf->no_last_mod_ignore ==0))
        /* HEAD requests */
        || r->header_only
        /* RFC2616 14.9.2 Cache-Control: no-store response indicating do not
         * cache, or stop now if you are trying to cache it */
        || ap_cache_liststr(cc_out, "no-store", NULL)
        /* RFC2616 14.9.1 Cache-Control: private
         * this object is marked for this user's eyes only. Behave
         * as a tunnel.
         */
        || ap_cache_liststr(cc_out, "private", NULL)
        /* RFC2616 14.8 Authorisation:
         * if authorisation is included in the request, we don't cache,
         * but we can cache if the following exceptions are true:
         * 1) If Cache-Control: s-maxage is included
         * 2) If Cache-Control: must-revalidate is included
         * 3) If Cache-Control: public is included
         */
        || (apr_table_get(r->headers_in, "Authorization") != NULL
            && !(ap_cache_liststr(cc_out, "s-maxage", NULL)
                 || ap_cache_liststr(cc_out, "must-revalidate", NULL)
                 || ap_cache_liststr(cc_out, "public", NULL)))
        /* or we've been asked not to cache it above */
        || r->no_cache) {

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "cache: response is not cachable");

        /* remove this object from the cache 
         * BillS Asks.. Why do we need to make this call to remove_url?
