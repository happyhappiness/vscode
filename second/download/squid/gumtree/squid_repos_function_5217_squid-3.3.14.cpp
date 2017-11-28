void
Auth::Negotiate::Config::parse(Auth::Config * scheme, int n_configured, char *param_str)
{
    if (strcasecmp(param_str, "program") == 0) {
        if (authenticateProgram)
            wordlistDestroy(&authenticateProgram);

        parse_wordlist(&authenticateProgram);

        requirePathnameExists("auth_param negotiate program", authenticateProgram->key);
    } else if (strcasecmp(param_str, "children") == 0) {
        authenticateChildren.parseConfig();
    } else if (strcasecmp(param_str, "keep_alive") == 0) {
        parse_onoff(&keep_alive);
    } else {
        debugs(29, DBG_CRITICAL, "ERROR: unrecognised Negotiate auth scheme parameter '" << param_str << "'");
    }
}