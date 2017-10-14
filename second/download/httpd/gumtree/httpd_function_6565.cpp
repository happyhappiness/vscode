static apr_status_t pass_response(h2_task *task, ap_filter_t *f, 
                                  h2_response_parser *parser) 
{
    apr_bucket *b;
    apr_status_t status;
    
    h2_headers *response = h2_headers_create(parser->http_status, 
                                             make_table(parser),
                                             NULL, task->pool);
    apr_brigade_cleanup(parser->tmp);
    b = h2_bucket_headers_create(task->c->bucket_alloc, response);
    APR_BRIGADE_INSERT_TAIL(parser->tmp, b);
    b = apr_bucket_flush_create(task->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(parser->tmp, b);                      
    status = ap_pass_brigade(f->next, parser->tmp);
    apr_brigade_cleanup(parser->tmp);
    
    /* reset parser for possible next response */
    parser->state = H2_RP_STATUS_LINE;
    apr_array_clear(parser->hlines);

    if (response->status >= 200) {
        task->output.sent_response = 1;
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, 
                  APLOGNO(03197) "h2_task(%s): passed response %d", 
                  task->id, response->status);
    return status;
}