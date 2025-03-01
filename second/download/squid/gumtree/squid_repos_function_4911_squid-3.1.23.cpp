void
AuthNTLMConfig::parse(AuthConfig * scheme, int n_configured, char *param_str)
{
    if (strcasecmp(param_str, "program") == 0) {
        if (authenticate)
            wordlistDestroy(&authenticate);

        parse_wordlist(&authenticate);

        requirePathnameExists("auth_param ntlm program", authenticate->key);
    } else if (strcasecmp(param_str, "children") == 0) {
        parse_int(&authenticateChildren);
    } else if (strcasecmp(param_str, "keep_alive") == 0) {
        parse_onoff(&keep_alive);
    } else {
        debugs(29, 0, "AuthNTLMConfig::parse: unrecognised ntlm auth scheme parameter '" << param_str << "'");
    }
}