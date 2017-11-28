void
Auth::Negotiate::Config::init(Auth::Config * scheme)
{
    if (authenticateProgram) {

        authnegotiate_initialised = 1;

        if (negotiateauthenticators == NULL)
            negotiateauthenticators = new statefulhelper("negotiateauthenticator");

        if (!proxy_auth_cache)
            proxy_auth_cache = hash_create((HASHCMP *) strcmp, 7921, hash_string);

        assert(proxy_auth_cache);

        negotiateauthenticators->cmdline = authenticateProgram;

        negotiateauthenticators->childs.updateLimits(authenticateChildren);

        negotiateauthenticators->ipc_type = IPC_STREAM;

        helperStatefulOpenServers(negotiateauthenticators);
    }
}