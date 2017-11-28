void
parse_pipelinePrefetch(int *var)
{
    char *token = ConfigParser::PeekAtToken();
    if (!token) {
        self_destruct();
        return;
    }

    if (!strcmp(token, "on")) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'pipeline_prefetch on' is deprecated. Please update to use 1 (or a higher number).");
        *var = 1;
        //pop the token
        (void)ConfigParser::NextToken();
    } else if (!strcmp(token, "off")) {
        debugs(0, DBG_PARSE_NOTE(2), "WARNING: 'pipeline_prefetch off' is deprecated. Please update to use '0'.");
        *var = 0;
        //pop the token
        (void)ConfigParser::NextToken();
    } else
        parse_int(var);
}