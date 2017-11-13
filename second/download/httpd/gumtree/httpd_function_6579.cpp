static void check_push(request_rec *r, const char *tag)
{
    const h2_config *conf = h2_config_rget(r);
    if (!r->expecting_100 
        && conf && conf->push_list && conf->push_list->nelts > 0) {
        int i, old_status;
        const char *old_line;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
                      "%s, early announcing %d resources for push",
                      tag, conf->push_list->nelts);
        for (i = 0; i < conf->push_list->nelts; ++i) {
            h2_push_res *push = &APR_ARRAY_IDX(conf->push_list, i, h2_push_res);
            apr_table_addn(r->headers_out, "Link", 
                           apr_psprintf(r->pool, "<%s>; rel=preload%s", 
                                        push->uri_ref, push->critical? "; critical" : ""));
        }
        old_status = r->status;
        old_line = r->status_line;
        r->status = 103;
        r->status_line = "103 Early Hints";
        ap_send_interim_response(r, 1);
        r->status = old_status;
        r->status_line = old_line;
    }
}