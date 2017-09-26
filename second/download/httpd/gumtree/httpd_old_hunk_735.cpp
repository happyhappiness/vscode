     * the headers out (including the Allow header)
     */

    return OK;
}

/* This routine is called by apr_table_do and merges all instances of
 * the passed field values into a single array that will be further
 * processed by some later routine.  Originally intended to help split
 * and recombine multiple Vary fields, though it is generic to any field
 * consisting of comma/space-separated tokens.
 */
static int uniq_field_values(void *d, const char *key, const char *val)
{
    apr_array_header_t *values;
    char *start;
    char *e;
    char **strpp;
    int  i;

    values = (apr_array_header_t *)d;

    e = apr_pstrdup(values->pool, val);

    do {
        /* Find a non-empty fieldname */

        while (*e == ',' || apr_isspace(*e)) {
            ++e;
        }
        if (*e == '\0') {
            break;
        }
        start = e;
        while (*e != '\0' && *e != ',' && !apr_isspace(*e)) {
            ++e;
        }
        if (*e != '\0') {
            *e++ = '\0';
        }

        /* Now add it to values if it isn't already represented.
         * Could be replaced by a ap_array_strcasecmp() if we had one.
         */
        for (i = 0, strpp = (char **) values->elts; i < values->nelts;
             ++i, ++strpp) {
            if (*strpp && strcasecmp(*strpp, start) == 0) {
                break;
            }
        }
        if (i == values->nelts) {  /* if not found */
            *(char **)apr_array_push(values) = start;
        }
    } while (*e != '\0');

    return 1;
}

/*
 * Since some clients choke violently on multiple Vary fields, or
 * Vary fields with duplicate tokens, combine any multiples and remove
 * any duplicates.
 */
static void fixup_vary(request_rec *r)
{
    apr_array_header_t *varies;

    varies = apr_array_make(r->pool, 5, sizeof(char *));

    /* Extract all Vary fields from the headers_out, separate each into
     * its comma-separated fieldname values, and then add them to varies
     * if not already present in the array.
     */
    apr_table_do((int (*)(void *, const char *, const char *))uniq_field_values,
                 (void *) varies, r->headers_out, "Vary", NULL);

    /* If we found any, replace old Vary fields with unique-ified value */

    if (varies->nelts > 0) {
        apr_table_setn(r->headers_out, "Vary",
                       apr_array_pstrcat(r->pool, varies, ','));
    }
}

AP_DECLARE(void) ap_set_content_type(request_rec *r, const char *ct)
{
    if (!ct) {
        r->content_type = NULL;
    }
    else if (!r->content_type || strcmp(r->content_type, ct)) {
        r->content_type = ct;

        /* Insert filters requested by the AddOutputFiltersByType 
         * configuration directive. Content-type filters must be 
         * inserted after the content handlers have run because 
         * only then, do we reliably know the content-type.
         */
        ap_add_output_filters_by_type(r);
    }
}

typedef struct header_filter_ctx {
    int headers_sent;
} header_filter_ctx;

AP_CORE_DECLARE_NONSTD(apr_status_t) ap_http_header_filter(ap_filter_t *f,
                                                           apr_bucket_brigade *b)
{
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    const char *clheader;
    const char *protocol;
    apr_bucket *e;
    apr_bucket_brigade *b2;
    header_struct h;
    header_filter_ctx *ctx = f->ctx;

    AP_DEBUG_ASSERT(!r->main);

    if (r->header_only) {
        if (!ctx) {
            ctx = f->ctx = apr_pcalloc(r->pool, sizeof(header_filter_ctx));
        }
        else if (ctx->headers_sent) {
            apr_brigade_destroy(b);
            return OK;
        }
    }

    APR_BRIGADE_FOREACH(e, b) {
        if (e->type == &ap_bucket_type_error) {
            ap_bucket_error *eb = e->data;

            ap_die(eb->status, r);
            return AP_FILTER_ERROR;
        }
    }

    if (r->assbackwards) {
        r->sent_bodyct = 1;
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, b);
    }

    /*
     * Now that we are ready to send a response, we need to combine the two
     * header field tables into a single table.  If we don't do this, our
     * later attempts to set or unset a given fieldname might be bypassed.
     */
    if (!apr_is_empty_table(r->err_headers_out)) {
        r->headers_out = apr_table_overlay(r->pool, r->err_headers_out,
                                           r->headers_out);
    }

    /*
     * Remove the 'Vary' header field if the client can't handle it.
     * Since this will have nasty effects on HTTP/1.1 caches, force
     * the response into HTTP/1.0 mode.
     *
     * Note: the force-response-1.0 should come before the call to
     *       basic_http_header_check()
     */
    if (apr_table_get(r->subprocess_env, "force-no-vary") != NULL) {
        apr_table_unset(r->headers_out, "Vary");
        r->proto_num = HTTP_VERSION(1,0);
        apr_table_set(r->subprocess_env, "force-response-1.0", "1");
    }
    else {
        fixup_vary(r);
    }

    /*
     * Now remove any ETag response header field if earlier processing
     * says so (such as a 'FileETag None' directive).
     */
    if (apr_table_get(r->notes, "no-etag") != NULL) {
        apr_table_unset(r->headers_out, "ETag");
    }

    /* determine the protocol and whether we should use keepalives. */
    basic_http_header_check(r, &protocol);
    ap_set_keepalive(r);

    if (r->chunked) {
        apr_table_mergen(r->headers_out, "Transfer-Encoding", "chunked");
        apr_table_unset(r->headers_out, "Content-Length");
    }

    apr_table_setn(r->headers_out, "Content-Type", 
                   ap_make_content_type(r, r->content_type));

    if (r->content_encoding) {
        apr_table_setn(r->headers_out, "Content-Encoding",
                       r->content_encoding);
    }

    if (!apr_is_empty_array(r->content_languages)) {
        int i;
        char **languages = (char **)(r->content_languages->elts);
        for (i = 0; i < r->content_languages->nelts; ++i) {
            apr_table_mergen(r->headers_out, "Content-Language", languages[i]);
        }
    }

    /*
     * Control cachability for non-cachable responses if not already set by
     * some other part of the server configuration.
     */
    if (r->no_cache && !apr_table_get(r->headers_out, "Expires")) {
        char *date = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
        ap_recent_rfc822_date(date, r->request_time);
        apr_table_addn(r->headers_out, "Expires", date);
    }

    /* This is a hack, but I can't find anyway around it.  The idea is that
     * we don't want to send out 0 Content-Lengths if it is a head request.
     * This happens when modules try to outsmart the server, and return
     * if they see a HEAD request.  Apache 1.3 handlers were supposed to
     * just return in that situation, and the core handled the HEAD.  In
     * 2.0, if a handler returns, then the core sends an EOS bucket down
     * the filter stack, and the content-length filter computes a C-L of
     * zero and that gets put in the headers, and we end up sending a
     * zero C-L to the client.  We can't just remove the C-L filter,
     * because well behaved 2.0 handlers will send their data down the stack,
     * and we will compute a real C-L for the head request. RBB
     */
    if (r->header_only
        && (clheader = apr_table_get(r->headers_out, "Content-Length"))
        && !strcmp(clheader, "0")) {
        apr_table_unset(r->headers_out, "Content-Length");
    }

    b2 = apr_brigade_create(r->pool, c->bucket_alloc);
    basic_http_header(r, b2, protocol);

    h.pool = r->pool;
    h.bb = b2;

    if (r->status == HTTP_NOT_MODIFIED) {
        apr_table_do((int (*)(void *, const char *, const char *)) form_header_field,
                     (void *) &h, r->headers_out,
                     "Connection",
                     "Keep-Alive",
                     "ETag",
                     "Content-Location",
                     "Expires",
                     "Cache-Control",
                     "Vary",
                     "Warning",
                     "WWW-Authenticate",
                     "Proxy-Authenticate",
                     "Set-Cookie",
                     "Set-Cookie2",
                     NULL);
    }
    else {
        send_all_header_fields(&h, r);
    }

    terminate_header(b2);

    ap_pass_brigade(f->next, b2);

    if (r->header_only) {
        apr_brigade_destroy(b);
        ctx->headers_sent = 1;
        return OK;
    }

    r->sent_bodyct = 1;         /* Whatever follows is real body stuff... */

    if (r->chunked) {
        /* We can't add this filter until we have already sent the headers.
         * If we add it before this point, then the headers will be chunked
         * as well, and that is just wrong.
         */
        ap_add_output_filter("CHUNK", NULL, r, r->connection);
    }

    /* Don't remove this filter until after we have added the CHUNK filter.
     * Otherwise, f->next won't be the CHUNK filter and thus the first
     * brigade won't be chunked properly.
     */
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, b);
}

/* Here we deal with getting the request message body from the client.
 * Whether or not the request contains a body is signaled by the presence
 * of a non-zero Content-Length or by a Transfer-Encoding: chunked.
 *
 * Note that this is more complicated than it was in Apache 1.1 and prior
 * versions, because chunked support means that the module does less.
 *
 * The proper procedure is this:
 *
 * 1. Call setup_client_block() near the beginning of the request
 *    handler. This will set up all the necessary properties, and will
 *    return either OK, or an error code. If the latter, the module should
 *    return that error code. The second parameter selects the policy to
 *    apply if the request message indicates a body, and how a chunked
 *    transfer-coding should be interpreted. Choose one of
 *
 *    REQUEST_NO_BODY          Send 413 error if message has any body
 *    REQUEST_CHUNKED_ERROR    Send 411 error if body without Content-Length
 *    REQUEST_CHUNKED_DECHUNK  If chunked, remove the chunks for me.
 *
 *    In order to use the last two options, the caller MUST provide a buffer
 *    large enough to hold a chunk-size line, including any extensions.
 *
 * 2. When you are ready to read a body (if any), call should_client_block().
 *    This will tell the module whether or not to read input. If it is 0,
 *    the module should assume that there is no message body to read.
 *    This step also sends a 100 Continue response to HTTP/1.1 clients,
 *    so should not be called until the module is *definitely* ready to
 *    read content. (otherwise, the point of the 100 response is defeated).
 *    Never call this function more than once.
 *
 * 3. Finally, call get_client_block in a loop. Pass it a buffer and its size.
 *    It will put data into the buffer (not necessarily a full buffer), and
 *    return the length of the input block. When it is done reading, it will
 *    return 0 if EOF, or -1 if there was an error.
 *    If an error occurs on input, we force an end to keepalive.
 */

AP_DECLARE(int) ap_setup_client_block(request_rec *r, int read_policy)
{
    const char *tenc = apr_table_get(r->headers_in, "Transfer-Encoding");
    const char *lenp = apr_table_get(r->headers_in, "Content-Length");

    r->read_body = read_policy;
    r->read_chunked = 0;
    r->remaining = 0;

    if (tenc) {
        if (strcasecmp(tenc, "chunked")) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Unknown Transfer-Encoding %s", tenc);
            return HTTP_NOT_IMPLEMENTED;
        }
        if (r->read_body == REQUEST_CHUNKED_ERROR) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "chunked Transfer-Encoding forbidden: %s", r->uri);
            return (lenp) ? HTTP_BAD_REQUEST : HTTP_LENGTH_REQUIRED;
        }

        r->read_chunked = 1;
    }
    else if (lenp) {
        int conversion_error = 0;
        char *endstr;

        errno = 0;
        r->remaining = strtol(lenp, &endstr, 10); /* depend on ANSI */

        /* See comments in ap_http_filter() */
        if (errno || (endstr && *endstr) || (r->remaining < 0)) {
            conversion_error = 1; 
        }

        if (conversion_error) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Invalid Content-Length");
            return HTTP_BAD_REQUEST;
        }
    }

    if ((r->read_body == REQUEST_NO_BODY)
        && (r->read_chunked || (r->remaining > 0))) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "%s with body is not allowed for %s", r->method, r->uri);
        return HTTP_REQUEST_ENTITY_TOO_LARGE;
    }

#ifdef AP_DEBUG
    {
        /* Make sure ap_getline() didn't leave any droppings. */
        core_request_config *req_cfg =
            (core_request_config *)ap_get_module_config(r->request_config,
                                                        &core_module);
        AP_DEBUG_ASSERT(APR_BRIGADE_EMPTY(req_cfg->bb));
    }
#endif

    return OK;
}

AP_DECLARE(int) ap_should_client_block(request_rec *r)
{
    /* First check if we have already read the request body */

    if (r->read_length || (!r->read_chunked && (r->remaining <= 0))) {
        return 0;
    }

    return 1;
}

/**
 * Parse a chunk extension, detect overflow.
 * There are two error cases:
 *  1) If the conversion would require too many bits, a -1 is returned.
 *  2) If the conversion used the correct number of bits, but an overflow
 *     caused only the sign bit to flip, then that negative number is
 *     returned.
 * In general, any negative number can be considered an overflow error.
 */
static long get_chunk_size(char *b)
{
    long chunksize = 0;
    size_t chunkbits = sizeof(long) * 8;

    ap_xlate_proto_from_ascii(b, strlen(b));

    /* Skip leading zeros */
    while (*b == '0') {
        ++b;
    }

    while (apr_isxdigit(*b) && (chunkbits > 0)) {
        int xvalue = 0;

        if (*b >= '0' && *b <= '9') {
            xvalue = *b - '0';
        }
        else if (*b >= 'A' && *b <= 'F') {
            xvalue = *b - 'A' + 0xa;
        }
        else if (*b >= 'a' && *b <= 'f') {
            xvalue = *b - 'a' + 0xa;
        }

        chunksize = (chunksize << 4) | xvalue;
        chunkbits -= 4;
        ++b;
    }
    if (apr_isxdigit(*b) && (chunkbits <= 0)) {
        /* overflow */
        return -1;
    }

    return chunksize;
}

/* get_client_block is called in a loop to get the request message body.
 * This is quite simple if the client includes a content-length
 * (the normal case), but gets messy if the body is chunked. Note that
 * r->remaining is used to maintain state across calls and that
 * r->read_length is the total number of bytes given to the caller
 * across all invocations.  It is messy because we have to be careful not
 * to read past the data provided by the client, since these reads block.
 * Returns 0 on End-of-body, -1 on error or premature chunk end.
 *
 */
AP_DECLARE(long) ap_get_client_block(request_rec *r, char *buffer,
                                     apr_size_t bufsiz)
{
    apr_status_t rv;
    apr_bucket_brigade *bb;

    if (r->remaining < 0 || (!r->read_chunked && r->remaining == 0)) {
        return 0;
    }

    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    if (bb == NULL) {
        r->connection->keepalive = AP_CONN_CLOSE;
        return -1;
    }

    rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                        APR_BLOCK_READ, bufsiz);
  
    /* We lose the failure code here.  This is why ap_get_client_block should
     * not be used.
     */
    if (rv != APR_SUCCESS) { 
        /* if we actually fail here, we want to just return and
         * stop trying to read data from the client.
         */
        r->connection->keepalive = AP_CONN_CLOSE;
        apr_brigade_destroy(bb);
        return -1;
    }

    /* If this fails, it means that a filter is written incorrectly and that
     * it needs to learn how to properly handle APR_BLOCK_READ requests by
     * returning data when requested.
     */
    AP_DEBUG_ASSERT(!APR_BRIGADE_EMPTY(bb));

    /* Check to see if EOS in the brigade.
     *
     * If so, we have to leave a nugget for the *next* ap_get_client_block
     * call to return 0.
     */
    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
        if (r->read_chunked) {
            r->remaining = -1;
        }
        else {
            r->remaining = 0;
        }
    }

    rv = apr_brigade_flatten(bb, buffer, &bufsiz);
    if (rv != APR_SUCCESS) {
        apr_brigade_destroy(bb);
        return -1;
    }

    /* XXX yank me? */
    r->read_length += bufsiz;

    apr_brigade_destroy(bb);
    return bufsiz;
}

/* In HTTP/1.1, any method can have a body.  However, most GET handlers
 * wouldn't know what to do with a request body if they received one.
 * This helper routine tests for and reads any message body in the request,
 * simply discarding whatever it receives.  We need to do this because
 * failing to read the request body would cause it to be interpreted
 * as the next request on a persistent connection.
 *
 * Since we return an error status if the request is malformed, this
 * routine should be called at the beginning of a no-body handler, e.g.,
 *
 *    if ((retval = ap_discard_request_body(r)) != OK) {
 *        return retval;
 *    }
 */
AP_DECLARE(int) ap_discard_request_body(request_rec *r)
{
    apr_bucket_brigade *bb;
    int rv, seen_eos;

    /* Sometimes we'll get in a state where the input handling has
     * detected an error where we want to drop the connection, so if
     * that's the case, don't read the data as that is what we're trying
     * to avoid.
     *
     * This function is also a no-op on a subrequest.
     */
    if (r->main || r->connection->keepalive == AP_CONN_CLOSE ||
        ap_status_drops_connection(r->status)) {
        return OK;
    }

    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    seen_eos = 0;
    do {
        apr_bucket *bucket;

        rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, HUGE_STRING_LEN);

        if (rv != APR_SUCCESS) {
            /* FIXME: If we ever have a mapping from filters (apr_status_t)
             * to HTTP error codes, this would be a good place for them.
             * 
             * If we received the special case AP_FILTER_ERROR, it means
             * that the filters have already handled this error.
             * Otherwise, we should assume we have a bad request.
             */
            if (rv == AP_FILTER_ERROR) {
                apr_brigade_destroy(bb);
                return rv;
            }
            else {
                apr_brigade_destroy(bb);
                return HTTP_BAD_REQUEST;
            }
        }

        APR_BRIGADE_FOREACH(bucket, bb) {
            const char *data;
            apr_size_t len;

            if (APR_BUCKET_IS_EOS(bucket)) {
                seen_eos = 1;
                break;
            }

            /* These are metadata buckets. */
            if (bucket->length == 0) {
                continue;
            }

            /* We MUST read because in case we have an unknown-length
             * bucket or one that morphs, we want to exhaust it.
             */
            rv = apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);
            if (rv != APR_SUCCESS) {
                apr_brigade_destroy(bb);
                return HTTP_BAD_REQUEST;
            }
        }
        apr_brigade_cleanup(bb);
    } while (!seen_eos);

    return OK;
}

AP_DECLARE(void) ap_set_accept_ranges(request_rec *r)
{
    core_dir_config *d = (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                                 &core_module);
    apr_table_setn(r->headers_out, "Accept-Ranges",
                  (d->max_ranges == AP_MAXRANGES_NORANGES) ? "none"
                                                           : "bytes");
}
static const char *add_optional_notes(request_rec *r,
                                      const char *prefix,
                                      const char *key,
                                      const char *suffix)
{
    const char *notes, *result;

    if ((notes = apr_table_get(r->notes, key)) == NULL) {
        result = apr_pstrcat(r->pool, prefix, suffix, NULL);
    }
    else {
        result = apr_pstrcat(r->pool, prefix, notes, suffix, NULL);
    }

    return result;
}

/* construct and return the default error message for a given
 * HTTP defined error code
 */
static const char *get_canned_error_string(int status,
