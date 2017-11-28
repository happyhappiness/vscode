static bool
compileRE(std::list<RegexPattern> &curlist, const char * RE, int flags)
{
    if (RE == NULL || *RE == '\0')
        return curlist.empty(); // XXX: old code did this. It looks wrong.

    regex_t comp;
    if (int errcode = regcomp(&comp, RE, flags)) {
        char errbuf[256];
        regerror(errcode, &comp, errbuf, sizeof errbuf);
        debugs(28, DBG_CRITICAL, cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "ERROR: invalid regular expression: '" << RE << "': " << errbuf);
        return false;
    }
    debugs(28, 2, "compiled '" << RE << "' with flags " << flags);

    curlist.emplace_back(flags, RE);
    curlist.back().regex = comp;

    return true;
}