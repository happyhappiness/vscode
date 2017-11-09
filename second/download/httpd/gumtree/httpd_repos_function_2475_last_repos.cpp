static apr_status_t parse_header(h2_response_parser *parser, char *line) {
    const char *hline;
    if (line[0] == ' ' || line[0] == '\t') {
        char **plast;
        /* continuation line from the header before this */
        while (line[0] == ' ' || line[0] == '\t') {
            ++line;
        }
        
        plast = apr_array_pop(parser->hlines);
        if (plast == NULL) {
            /* not well formed */
            return APR_EINVAL;
        }
        hline = apr_psprintf(parser->task->pool, "%s %s", *plast, line);
    }
    else {
        /* new header line */
        hline = apr_pstrdup(parser->task->pool, line);
    }
    APR_ARRAY_PUSH(parser->hlines, const char*) = hline; 
    return APR_SUCCESS;
}