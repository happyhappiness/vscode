static apr_table_t *make_table(h2_response_parser *parser)
{
    h2_task *task = parser->task;
    apr_array_header_t *hlines = parser->hlines;
    if (hlines) {
        apr_table_t *headers = apr_table_make(task->pool, hlines->nelts);        
        int i;
        
        for (i = 0; i < hlines->nelts; ++i) {
            char *hline = ((char **)hlines->elts)[i];
            char *sep = ap_strchr(hline, ':');
            if (!sep) {
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, task->c,
                              APLOGNO(02955) "h2_task(%s): invalid header[%d] '%s'",
                              task->id, i, (char*)hline);
                /* not valid format, abort */
                return NULL;
            }
            (*sep++) = '\0';
            while (*sep == ' ' || *sep == '\t') {
                ++sep;
            }
            
            if (!h2_util_ignore_header(hline)) {
                apr_table_merge(headers, hline, sep);
            }
        }
        return headers;
    }
    else {
        return apr_table_make(task->pool, 0);        
    }
}