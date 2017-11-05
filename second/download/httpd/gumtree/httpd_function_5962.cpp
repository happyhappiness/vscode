apr_status_t h2_from_h1_parse_response(h2_task *task, ap_filter_t *f, 
                                       apr_bucket_brigade *bb)
{
    h2_response_parser *parser = task->output.rparser;
    char line[HUGE_STRING_LEN];
    apr_status_t status = APR_SUCCESS;

    if (!parser) {
        parser = apr_pcalloc(task->pool, sizeof(*parser));
        parser->task = task;
        parser->state = H2_RP_STATUS_LINE;
        parser->hlines = apr_array_make(task->pool, 10, sizeof(char *));
        task->output.rparser = parser;
    }
    
    while (!APR_BRIGADE_EMPTY(bb) && status == APR_SUCCESS) {
        switch (parser->state) {
            case H2_RP_STATUS_LINE:
            case H2_RP_HEADER_LINE:
                status = get_line(parser, bb, line, sizeof(line));
                if (status == APR_EAGAIN) {
                    /* need more data */
                    return APR_SUCCESS;
                }
                else if (status != APR_SUCCESS) {
                    return status;
                }
                if (parser->state == H2_RP_STATUS_LINE) {
                    /* instead of parsing, just take it directly */
                    status = parse_status(task, line);
                }
                else if (line[0] == '\0') {
                    /* end of headers, pass response onward */
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                                  "h2_task(%s): end of response", task->id);
                    return pass_response(task, f, parser);
                }
                else {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                                  "h2_task(%s): response header %s", task->id, line);
                    status = parse_header(parser, line);
                }
                break;
                
            default:
                return status;
        }
    }
    return status;
}