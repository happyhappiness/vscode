void
AuthDigestConfig::parse(AuthConfig * scheme, int n_configured, char *param_str)
{
    if (strcasecmp(param_str, "program") == 0) {
        if (authenticate)
            wordlistDestroy(&authenticate);

        parse_wordlist(&authenticate);

        requirePathnameExists("auth_param digest program", authenticate->key);
    } else if (strcasecmp(param_str, "children") == 0) {
        parse_int(&authenticateChildren);
    } else if (strcasecmp(param_str, "realm") == 0) {
        parse_eol(&digestAuthRealm);
    } else if (strcasecmp(param_str, "nonce_garbage_interval") == 0) {
        parse_time_t(&nonceGCInterval);
    } else if (strcasecmp(param_str, "nonce_max_duration") == 0) {
        parse_time_t(&noncemaxduration);
    } else if (strcasecmp(param_str, "nonce_max_count") == 0) {
        parse_int((int *) &noncemaxuses);
    } else if (strcasecmp(param_str, "nonce_strictness") == 0) {
        parse_onoff(&NonceStrictness);
    } else if (strcasecmp(param_str, "check_nonce_count") == 0) {
        parse_onoff(&CheckNonceCount);
    } else if (strcasecmp(param_str, "post_workaround") == 0) {
        parse_onoff(&PostWorkaround);
    } else if (strcasecmp(param_str, "utf8") == 0) {
        parse_onoff(&utf8);
    } else {
        debugs(29, 0, "unrecognised digest auth scheme parameter '" << param_str << "'");
    }
}