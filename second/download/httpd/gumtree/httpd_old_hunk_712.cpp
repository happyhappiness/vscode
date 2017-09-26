    rr->path_info = r->path_info;       /* hard to get right; see mod_cgi.c */
    rr->args = r->args;

    /* Force sub_req to be treated as a CGI request, even if ordinary
     * typing rules would have called it something else.
     */

    ap_set_content_type(rr, CGI_MAGIC_TYPE);

    /* Run it. */

    rr_status = ap_run_sub_req(rr);
    if (ap_is_HTTP_REDIRECT(rr_status)) {
        apr_size_t len_loc;
        const char *location = apr_table_get(rr->headers_out, "Location");
        conn_rec *c = r->connection;

        location = ap_escape_html(rr->pool, location);
        len_loc = strlen(location);

        /* XXX: if most of this stuff is going to get copied anyway,
         * it'd be more efficient to pstrcat it into a single pool buffer
         * and a single pool bucket */

        tmp_buck = apr_bucket_immortal_create("<A HREF=\"",
                                              sizeof("<A HREF=\"") - 1,
                                              c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
        tmp2_buck = apr_bucket_heap_create(location, len_loc, NULL,
                                           c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
        tmp2_buck = apr_bucket_immortal_create("\">", sizeof("\">") - 1,
                                               c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
        tmp2_buck = apr_bucket_heap_create(location, len_loc, NULL,
                                           c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
        tmp2_buck = apr_bucket_immortal_create("</A>", sizeof("</A>") - 1,
                                               c->bucket_alloc);
        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);

        if (*inserted_head == NULL) {
            *inserted_head = tmp_buck;
        }
    }

    ap_destroy_sub_req(rr);

    return 0;
}


static int include_cmd(include_ctx_t *ctx, apr_bucket_brigade **bb,
                       const char *command, request_rec *r, ap_filter_t *f)
{
    cgi_exec_info_t  e_info;
    const char   **argv;
    apr_file_t    *script_out = NULL, *script_in = NULL, *script_err = NULL;
    apr_bucket_brigade *bcgi;
    apr_bucket *b;
    apr_status_t rv;

    add_ssi_vars(r);

    e_info.process_cgi = 0;
    e_info.cmd_type    = APR_SHELLCMD;
    e_info.detached    = 0;
    e_info.in_pipe     = APR_NO_PIPE;
    e_info.out_pipe    = APR_FULL_BLOCK;
    e_info.err_pipe    = APR_NO_PIPE;
    e_info.prog_type   = RUN_AS_SSI;
    e_info.bb          = bb;
    e_info.ctx         = ctx;
    e_info.next        = f->next;

    if ((rv = cgi_build_command(&command, &argv, r, r->pool, &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "don't know how to spawn cmd child process: %s", 
                      r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* run the script in its own process */
    if ((rv = run_cgi_child(&script_out, &script_in, &script_err,
                            command, argv, r, r->pool,
                            &e_info)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "couldn't spawn child process: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    bcgi = apr_brigade_create(r->pool, f->c->bucket_alloc);
    b = apr_bucket_pipe_create(script_in, f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bcgi, b);
    ap_pass_brigade(f->next, bcgi);

    /* We can't close the pipe here, because we may return before the
     * full CGI has been sent to the network.  That's okay though,
     * because we can rely on the pool to close the pipe for us.
     */

    return 0;
}

static int handle_exec(include_ctx_t *ctx, apr_bucket_brigade **bb,
                       request_rec *r, ap_filter_t *f, apr_bucket *head_ptr,
                       apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    char *file = r->filename;
    apr_bucket  *tmp_buck;
    char parsed_string[MAX_STRING_LEN];

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        if (ctx->flags & FLAG_NO_EXEC) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "exec used but not allowed in %s", r->filename);
            CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
        }
        else {
            while (1) {
                cgi_pfn_gtv(ctx, &tag, &tag_val, 1);
                if (tag_val == NULL) {
                    if (tag == NULL) {
                        return 0;
                    }
                    else {
                        return 1;
                    }
                }
                if (!strcmp(tag, "cmd")) {
                    cgi_pfn_ps(r, ctx, tag_val, parsed_string,
                               sizeof(parsed_string), 1);
                    if (include_cmd(ctx, bb, parsed_string, r, f) == -1) {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                    "execution failure for parameter \"%s\" "
                                    "to tag exec in file %s", tag, r->filename);
                        CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr,
                                            *inserted_head);
                    }
                }
                else if (!strcmp(tag, "cgi")) {
                    apr_status_t retval = APR_SUCCESS;

                    cgi_pfn_ps(r, ctx, tag_val, parsed_string,
                               sizeof(parsed_string), 0);

                    SPLIT_AND_PASS_PRETAG_BUCKETS(*bb, ctx, f->next, retval);
                    if (retval != APR_SUCCESS) {
                        return retval;
                    }

                    if (include_cgi(parsed_string, r, f->next, head_ptr,
                                    inserted_head) == -1) {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                      "invalid CGI ref \"%s\" in %s",
                                      tag_val, file);
                        CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr,
                                            *inserted_head);
                    }
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "unknown parameter \"%s\" to tag exec in %s",
                                  tag, file);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr,
                                        *inserted_head);
                }
            }
        }
    }
    return 0;
}


/*============================================================================
 *============================================================================
 * This is the end of the cgi filter code moved from mod_include.
