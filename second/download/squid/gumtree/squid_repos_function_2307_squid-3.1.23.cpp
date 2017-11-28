int
accessLogParseLogFormat(logformat_token ** fmt, char *def)
{
    char *cur, *eos;
    logformat_token *new_lt, *last_lt;
    enum log_quote quote = LOG_QUOTE_NONE;

    debugs(46, 2, "accessLogParseLogFormat: got definition '" << def << "'");

    /* very inefficent parser, but who cares, this needs to be simple */
    /* First off, let's tokenize, we'll optimize in a second pass.
     * A token can either be a %-prefixed sequence (usually a dynamic
     * token but it can be an escaped sequence), or a string. */
    cur = def;
    eos = def + strlen(def);
    *fmt = new_lt = last_lt = (logformat_token *)xmalloc(sizeof(logformat_token));
    cur += accessLogGetNewLogFormatToken(new_lt, cur, &quote);

    while (cur < eos) {
        new_lt = (logformat_token *)xmalloc(sizeof(logformat_token));
        last_lt->next = new_lt;
        last_lt = new_lt;
        cur += accessLogGetNewLogFormatToken(new_lt, cur, &quote);
    }

    return 1;
}