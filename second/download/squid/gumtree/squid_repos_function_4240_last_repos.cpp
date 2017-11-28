void
ACLRegexData::parse()
{
    debugs(28, 2, "new Regex line or file");

    SBufList sl;
    while (char *t = ConfigParser::RegexStrtokFile()) {
        const char *clean = removeUnnecessaryWildcards(t);
        if (strlen(clean) > BUFSIZ-1) {
            debugs(28, DBG_CRITICAL, cfg_filename << " line " << config_lineno << ": " << config_input_line);
            debugs(28, DBG_CRITICAL, "ERROR: Skipping regular expression. Larger than " << BUFSIZ-1 << " characters: '" << clean << "'");
        } else {
            debugs(28, 3, "buffering RE '" << clean << "'");
            sl.emplace_back(clean);
        }
    }

    if (!compileOptimisedREs(data, sl)) {
        debugs(28, DBG_IMPORTANT, "WARNING: optimisation of regular expressions failed; using fallback method without optimisation");
        compileUnoptimisedREs(data, sl);
    }
}