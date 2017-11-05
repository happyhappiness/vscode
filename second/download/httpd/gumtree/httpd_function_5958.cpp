static apr_status_t get_line(h2_response_parser *parser, apr_bucket_brigade *bb, 
                             char *line, apr_size_t len)
{
    h2_task *task = parser->task;
    apr_status_t status;
    
    if (!parser->tmp) {
        parser->tmp = apr_brigade_create(task->pool, task->c->bucket_alloc);
    }
    status = apr_brigade_split_line(parser->tmp, bb, APR_BLOCK_READ, 
                                    HUGE_STRING_LEN);
    if (status == APR_SUCCESS) {
        --len;
        status = apr_brigade_flatten(parser->tmp, line, &len);
        if (status == APR_SUCCESS) {
            /* we assume a non-0 containing line and remove trailing crlf. */
            line[len] = '\0';
            if (len >= 2 && !strcmp(H2_CRLF, line + len - 2)) {
                len -= 2;
                line[len] = '\0';
                apr_brigade_cleanup(parser->tmp);
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c,
                              "h2_task(%s): read response line: %s", 
                              task->id, line);
            }
            else {
                /* this does not look like a complete line yet */
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c,
                              "h2_task(%s): read response, incomplete line: %s", 
                              task->id, line);
                return APR_EAGAIN;
            }
        }
    }
    apr_brigade_cleanup(parser->tmp);
    return status;
}