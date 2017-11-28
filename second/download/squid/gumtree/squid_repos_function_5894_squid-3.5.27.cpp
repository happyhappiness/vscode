void
Auth::Digest::Config::parse(Auth::Config * scheme, int n_configured, char *param_str)
{
    if (strcmp(param_str, "program") == 0) {
        if (authenticateProgram)
            wordlistDestroy(&authenticateProgram);

        parse_wordlist(&authenticateProgram);

        requirePathnameExists("auth_param digest program", authenticateProgram->key);
    } else if (strcmp(param_str, "nonce_garbage_interval") == 0) {
        parse_time_t(&nonceGCInterval);
    } else if (strcmp(param_str, "nonce_max_duration") == 0) {
        parse_time_t(&noncemaxduration);
    } else if (strcmp(param_str, "nonce_max_count") == 0) {
        parse_int((int *) &noncemaxuses);
    } else if (strcmp(param_str, "nonce_strictness") == 0) {
        parse_onoff(&NonceStrictness);
    } else if (strcmp(param_str, "check_nonce_count") == 0) {
        parse_onoff(&CheckNonceCount);
    } else if (strcmp(param_str, "post_workaround") == 0) {
        parse_onoff(&PostWorkaround);
    } else if (strcmp(param_str, "utf8") == 0) {
        parse_onoff(&utf8);
    } else
        Auth::Config::parse(scheme, n_configured, param_str);
}