    /* We are putting the socket discriptor into an apr_file_t so that we can
     * use a pipe bucket to send the data to the client.  APR will create
     * a cleanup for the apr_file_t which will close the socket, so we'll
     * get rid of the cleanup we registered when we created the socket.
     */
    apr_os_pipe_put_ex(&tempsock, &sd, 1, r->pool);
    apr_pool_cleanup_kill(r->pool, (void *)((long)sd), close_unix_socket);

    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pipe_create(tempsock,
                            f->c->bucket_alloc));
    ctx->flush_now = 1;

    return APR_SUCCESS;
}

static apr_status_t handle_exec(include_ctx_t *ctx, ap_filter_t *f,
                                apr_bucket_brigade *bb)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    request_rec *r = f->r;
    char *file = r->filename;
    char parsed_string[MAX_STRING_LEN];

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for exec element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    if (ctx->flags & SSI_FLAG_NO_EXEC) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "exec used but not allowed "
                      "in %s", r->filename);
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    while (1) {
        cgid_pfn_gtv(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
            break;
        }

        if (!strcmp(tag, "cmd")) {
            apr_status_t rv;

            cgid_pfn_ps(ctx, tag_val, parsed_string, sizeof(parsed_string),
                        SSI_EXPAND_LEAVE_NAME);

            rv = include_cmd(ctx, f, bb, parsed_string);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "execution failure for parameter \"%s\" "
                              "to tag exec in file %s", tag, r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }
        }
        else if (!strcmp(tag, "cgi")) {
            apr_status_t rv;

            cgid_pfn_ps(ctx, tag_val, parsed_string, sizeof(parsed_string),
                        SSI_EXPAND_DROP_NAME);

            rv = include_cgi(ctx, f, bb, parsed_string);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "invalid CGI ref "
                              "\"%s\" in %s", tag_val, file);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
                          "\"%s\" to tag exec in %s", tag, file);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}
/*============================================================================
 *============================================================================
 * This is the end of the cgi filter code moved from mod_include.
 *============================================================================
 *============================================================================*/


static void register_hook(apr_pool_t *p)
{
    static const char * const aszPre[] = { "mod_include.c", NULL };

    ap_hook_pre_config(cgid_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(cgid_init, aszPre, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(cgid_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA cgid_module = {
    STANDARD20_MODULE_STUFF,
    NULL, /* dir config creater */
    NULL, /* dir merger --- default is to override */
    create_cgid_config, /* server config */
    merge_cgid_config, /* merge server config */
    cgid_cmds, /* command table */
    register_hook /* register_handlers */
};

