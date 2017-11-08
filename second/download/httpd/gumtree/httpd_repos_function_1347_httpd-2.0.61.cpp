static int handle_include(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                         request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                         apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    apr_bucket  *tmp_buck;
    char *parsed_string;
    int loglevel = APLOG_ERR;

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
            if (tag_val == NULL) {
                if (tag == NULL) {
                    return (0);
                }
                else {
                    return (1);
                }
            }
            if (!strcmp(tag, "virtual") || !strcmp(tag, "file")) {
                request_rec *rr = NULL;
                char *error_fmt = NULL;
                apr_status_t rc = APR_SUCCESS;

                SPLIT_AND_PASS_PRETAG_BUCKETS(*bb, ctx, f->next, rc);
                if (rc != APR_SUCCESS) {
                    return rc;
                }
 
                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
                                                    MAX_STRING_LEN, 0);
                if (tag[0] == 'f') {
                    /* XXX: Port to apr_filepath_merge
                     * be safe; only files in this directory or below allowed 
                     */
                    if (!is_only_below(parsed_string)) {
                        error_fmt = "unable to include file \"%s\" "
                                    "in parsed file %s";
                    }
                    else {
                        rr = ap_sub_req_lookup_uri(parsed_string, r, f->next);
                    }
                }
                else {
                    rr = ap_sub_req_lookup_uri(parsed_string, r, f->next);
                }

                if (!error_fmt && rr->status != HTTP_OK) {
                    error_fmt = "unable to include \"%s\" in parsed file %s";
                }

                if (!error_fmt && (ctx->flags & FLAG_NO_EXEC) && 
                    rr->content_type && 
                    (strncmp(rr->content_type, "text/", 5))) {
                    error_fmt = "unable to include potential exec \"%s\" "
                        "in parsed file %s";
                }

                /* See the Kludge in send_parsed_file for why */
                /* Basically, it puts a bread crumb in here, then looks */
                /*   for the crumb later to see if its been here.       */
                if (rr) 
                    ap_set_module_config(rr->request_config, 
                                         &include_module, r);

                if (!error_fmt && ap_run_sub_req(rr)) {
                    error_fmt = "unable to include \"%s\" in parsed file %s";
                }
                if (error_fmt) {
                    ap_log_rerror(APLOG_MARK, loglevel,
                                  0, r, error_fmt, tag_val, r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                }
                
                /* Do *not* destroy the subrequest here; it may have allocated
                 * variables in this r->subprocess_env in the subrequest's
                 * r->pool, so that pool must survive as long as this request.
                 * Yes, this is a memory leak. */
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" to tag include in %s",
                            tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return 1;
            }
        }
    }
    return 0;
}