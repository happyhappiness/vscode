void
Auth::Basic::Config::parse(Auth::Config * scheme, int n_configured, char *param_str)
{
    if (strcasecmp(param_str, "program") == 0) {
        if (authenticateProgram)
            wordlistDestroy(&authenticateProgram);

        parse_wordlist(&authenticateProgram);

        requirePathnameExists("auth_param basic program", authenticateProgram->key);
    } else if (strcasecmp(param_str, "children") == 0) {
        authenticateChildren.parseConfig();
    } else if (strcasecmp(param_str, "realm") == 0) {
        parse_eol(&basicAuthRealm);
    } else if (strcasecmp(param_str, "credentialsttl") == 0) {
        parse_time_t(&credentialsTTL);
    } else if (strcasecmp(param_str, "casesensitive") == 0) {
        parse_onoff(&casesensitive);
    } else if (strcasecmp(param_str, "utf8") == 0) {
        parse_onoff(&utf8);
    } else {
        debugs(29, DBG_CRITICAL, HERE << "unrecognised basic auth scheme parameter '" << param_str << "'");
    }
}