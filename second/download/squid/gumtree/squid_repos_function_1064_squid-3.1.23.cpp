static void
free_authparam(authConfig * cfg)
{
    AuthConfig *scheme;
    /* DON'T FREE THESE FOR RECONFIGURE */

    if (reconfiguring)
        return;

    while (cfg->size()) {
        scheme = cfg->pop_back();
        scheme->done();
    }
}