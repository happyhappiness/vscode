static int handle_map_file(request_rec *r)
{
    negotiation_state *neg;
    apr_file_t *map;
    var_rec *best;
    int res;
    char *udir;
    const char *new_req;

    if(strcmp(r->handler,MAP_FILE_MAGIC_TYPE) && strcmp(r->handler,"type-map"))
        return DECLINED;

    neg = parse_accept_headers(r);
    if ((res = read_type_map(&map, neg, r))) {
        return res;
    }

    res = do_negotiation(r, neg, &best, 0);
    if (res != 0) return res;

    if (best->body)
    {
        conn_rec *c = r->connection;
        apr_bucket_brigade *bb;
        apr_bucket *e;

        ap_allow_standard_methods(r, REPLACE_ALLOW, M_GET, M_OPTIONS,
                                  M_POST, -1);
        /* XXX: ?
         * if (r->method_number == M_OPTIONS) {
         *    return ap_send_http_options(r);
         *}
         */
        if (r->method_number != M_GET && r->method_number != M_POST) {
            return HTTP_METHOD_NOT_ALLOWED;
        }

        /* ### These may be implemented by adding some 'extra' info
         *     of the file offset onto the etag
         * ap_update_mtime(r, r->finfo.mtime);
         * ap_set_last_modified(r);
         * ap_set_etag(r);
         */
        ap_set_accept_ranges(r);
        ap_set_content_length(r, best->bytes);

        /* set MIME type and charset as negotiated */
        if (best->mime_type && *best->mime_type) {
            if (best->content_charset && *best->content_charset) {
                ap_set_content_type(r, apr_pstrcat(r->pool,
                                                   best->mime_type,
                                                   "; charset=",
                                                   best->content_charset,
                                                   NULL));
            }
            else {
                ap_set_content_type(r, apr_pstrdup(r->pool, best->mime_type));
            }
        }

        /* set Content-language(s) as negotiated */
        if (best->content_languages && best->content_languages->nelts) {
            r->content_languages = apr_array_copy(r->pool,
                                                  best->content_languages);
        }

        /* set Content-Encoding as negotiated */
        if (best->content_encoding && *best->content_encoding) {
            r->content_encoding = apr_pstrdup(r->pool,
                                              best->content_encoding);
        }

        if ((res = ap_meets_conditions(r)) != OK) {
            return res;
        }

        if ((res = ap_discard_request_body(r)) != OK) {
            return res;
        }
        bb = apr_brigade_create(r->pool, c->bucket_alloc);
        e = apr_bucket_file_create(map, best->body,
                                   (apr_size_t)best->bytes, r->pool,
                                   c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);
        e = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);

        return ap_pass_brigade(r->output_filters, bb);
    }

    if (r->path_info && *r->path_info) {
        /* remove any path_info from the end of the uri before trying
         * to change the filename.  r->path_info from the original
         * request is passed along on the redirect.
         */
        r->uri[ap_find_path_info(r->uri, r->path_info)] = '\0';
    }
    udir = ap_make_dirstr_parent(r->pool, r->uri);
    udir = ap_escape_uri(r->pool, udir);
    if (r->args) {
        if (r->path_info) {
            new_req = apr_pstrcat(r->pool, udir, best->file_name,
                                  r->path_info, "?", r->args, NULL);
        }
        else {
            new_req = apr_pstrcat(r->pool, udir, best->file_name,
                                  "?", r->args, NULL);
        }
    }
    else {
        new_req = apr_pstrcat(r->pool, udir, best->file_name,
                              r->path_info, NULL);
    }
    ap_internal_redirect(new_req, r);
    return OK;
}