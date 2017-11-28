static void
aclParseRegexList(RegexList **curlist)
{
    char *t;
    wordlist *wl = NULL;

    debugs(28, 2, HERE << "aclParseRegexList: new Regex line or file");

    while ((t = ConfigParser::RegexStrtokFile()) != NULL) {
        const char *clean = removeUnnecessaryWildcards(t);
        if (strlen(clean) > BUFSIZ-1) {
            debugs(28, DBG_CRITICAL, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
            debugs(28, DBG_CRITICAL, "ERROR: Skipping regular expression. Larger than " << BUFSIZ-1 << " characters: '" << clean << "'");
        } else {
            debugs(28, 3, "aclParseRegexList: buffering RE '" << clean << "'");
            wordlistAdd(&wl, clean);
        }
    }

    if (!compileOptimisedREs(curlist, wl)) {
        debugs(28, DBG_IMPORTANT, "WARNING: optimisation of regular expressions failed; using fallback method without optimisation");
        compileUnoptimisedREs(curlist, wl);
    }

    wordlistDestroy(&wl);
}