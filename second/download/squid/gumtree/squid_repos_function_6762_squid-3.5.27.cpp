bool
Format::Format::parse(const char *def)
{
    const char *cur, *eos;
    Token *new_lt, *last_lt;
    enum Quoting quote = LOG_QUOTE_NONE;

    debugs(46, 2, HERE << "got definition '" << def << "'");

    if (format) {
        debugs(46, DBG_IMPORTANT, "WARNING: existing format for '" << name << " " << def << "'");
        return false;
    }

    /* very inefficent parser, but who cares, this needs to be simple */
    /* First off, let's tokenize, we'll optimize in a second pass.
     * A token can either be a %-prefixed sequence (usually a dynamic
     * token but it can be an escaped sequence), or a string. */
    cur = def;
    eos = def + strlen(def);
    format = new_lt = last_lt = new Token;
    cur += new_lt->parse(cur, &quote);

    while (cur < eos) {
        new_lt = new Token;
        last_lt->next = new_lt;
        last_lt = new_lt;
        cur += new_lt->parse(cur, &quote);
    }

    return true;
}