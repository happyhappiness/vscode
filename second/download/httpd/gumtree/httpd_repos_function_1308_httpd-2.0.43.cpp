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
                if (error_fmt == NULL) {
                    /* try to avoid recursive includes.  We do this by walking
                     * up the r->main list of subrequests, and at each level
                     * walking back through any internal redirects.  At each
                     * step, we compare the filenames and the URIs.  
                     *
                     * The filename comparison catches a recursive include
                     * with an ever-changing URL, eg.
                     * <!--#include virtual=
                     *      "$REQUEST_URI/$QUERY_STRING?$QUERY_STRING/x" -->
                     * which, although they would eventually be caught because
                     * we have a limit on the length of files, etc., can 
                     * recurse for a while.
                     *
                     * The URI comparison catches the case where the filename
                     * is changed while processing the request, so the 
                     * current name is never the same as any previous one.
                     * This can happen with "DocumentRoot /foo" when you
                     * request "/" on the server and it includes "/".
                     * This only applies to modules such as mod_dir that 
                     * (somewhat improperly) mess with r->filename outside 
                     * of a filename translation phase.
                     */
                    int founddupe = 0;
                    request_rec *p;
                    for (p = r; p != NULL && !founddupe; p = p->main) {
                        request_rec *q;
                        for (q = p; q != NULL; q = q->prev) {
                            if ((q->filename && rr->filename && 
                                (strcmp(q->filename, rr->filename) == 0)) ||
                                ((*q->uri == '/') && 
                                 (strcmp(q->uri, rr->uri) == 0)))
                            {
                                founddupe = 1;
                                break;
                            }
                        }
                    }

                    if (p != NULL) {
                        error_fmt = "Recursive include of \"%s\" "
                            "in parsed file %s";
                    }
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

                /* destroy the sub request */
                if (rr != NULL) {
                    ap_destroy_sub_req(rr);
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" to tag include in %s",
                            tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            }
        }
    }
    return 0;
}