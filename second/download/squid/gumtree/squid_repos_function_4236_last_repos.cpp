static const char *
removeUnnecessaryWildcards(char * t)
{
    char * orig = t;

    if (strncmp(t, "^.*", 3) == 0)
        t += 3;

    /* NOTE: an initial '.' might seem unnessary but is not;
     * it can be a valid requirement that cannot be optimised
     */
    while (*t == '.'  &&  *(t+1) == '*') {
        t += 2;
    }

    if (*t == '\0') {
        debugs(28, DBG_IMPORTANT, cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_IMPORTANT, "WARNING: regular expression '" << orig << "' has only wildcards and matches all strings. Using '.*' instead.");
        return ".*";
    }
    if (t != orig) {
        debugs(28, DBG_IMPORTANT, cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_IMPORTANT, "WARNING: regular expression '" << orig << "' has unnecessary wildcard(s). Using '" << t << "' instead.");
    }

    return t;
}