void
Auth::Ntlm::Config::parse(Auth::Config * scheme, int n_configured, char *param_str)
{
    if (strcmp(param_str, "program") == 0) {
        if (authenticateProgram)
            wordlistDestroy(&authenticateProgram);

        parse_wordlist(&authenticateProgram);

        requirePathnameExists("auth_param ntlm program", authenticateProgram->key);
    } else if (strcmp(param_str, "children") == 0) {
        authenticateChildren.parseConfig();
    } else if (strcmp(param_str, "keep_alive") == 0) {
        parse_onoff(&keep_alive);
    } else {
        debugs(29, DBG_CRITICAL, "ERROR unrecognised NTLM auth scheme parameter '" << param_str << "'");
    }
}