void
AuthNegotiateConfig::init(AuthConfig * scheme)
{
    if (authenticate) {

        authnegotiate_initialised = 1;

        if (negotiateauthenticators == NULL)
            negotiateauthenticators = helperStatefulCreate("negotiateauthenticator");

        if (!proxy_auth_cache)
            proxy_auth_cache = hash_create((HASHCMP *) strcmp, 7921, hash_string);

        assert(proxy_auth_cache);

        negotiateauthenticators->cmdline = authenticate;

        negotiateauthenticators->n_to_start = authenticateChildren;

        negotiateauthenticators->ipc_type = IPC_STREAM;

        helperStatefulOpenServers(negotiateauthenticators);

        CBDATA_INIT_TYPE(authenticateStateData);
    }
}