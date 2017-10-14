static int handle_echo(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                       request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                       apr_bucket **inserted_head)
{
    char       *tag       = NULL;
    char       *tag_val   = NULL;
    const char *echo_text = NULL;
    apr_bucket  *tmp_buck;
    apr_size_t e_len;
    enum {E_NONE, E_URL, E_ENTITY} encode;

    encode = E_ENTITY;

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
            if (tag_val == NULL) {
                if (tag != NULL) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            if (!strcmp(tag, "var")) {
                conn_rec *c = r->connection;
                const char *val =
                    get_include_var(r, ctx,
                                    ap_ssi_parse_string(r, ctx, tag_val, NULL,
                                                        MAX_STRING_LEN, 0));
                if (val) {
                    switch(encode) {
                    case E_NONE:   
                        echo_text = val;
                        break;
                    case E_URL:
                        echo_text = ap_escape_uri(r->pool, val);  
                        break;
                    case E_ENTITY: 
                        echo_text = ap_escape_html(r->pool, val); 
                        break;
                    }

                    e_len = strlen(echo_text);
                    tmp_buck = apr_bucket_pool_create(echo_text, e_len,
                                                      r->pool, c->bucket_alloc);
                }
                else {
                    include_server_config *sconf= 
                        ap_get_module_config(r->server->module_config,
                                             &include_module);
                    tmp_buck = apr_bucket_pool_create(sconf->undefinedEcho, 
                                                      sconf->undefinedEchoLen,
                                                      r->pool, c->bucket_alloc);
                }
                APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
                if (*inserted_head == NULL) {
                    *inserted_head = tmp_buck;
                }
            }
            else if (!strcmp(tag, "encoding")) {
                if (!strcasecmp(tag_val, "none")) encode = E_NONE;
                else if (!strcasecmp(tag_val, "url")) encode = E_URL;
                else if (!strcasecmp(tag_val, "entity")) encode = E_ENTITY;
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "unknown value \"%s\" to parameter \"encoding\" of "
                           "tag echo in %s", tag_val, r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" in tag echo of %s",
                            tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return 1;
            }

        }
    }
    return 0;
}