void
AuthNTLMConfig::init(AuthConfig * scheme)
{
    if (authenticate) {

        authntlm_initialised = 1;

        if (ntlmauthenticators == NULL)
            ntlmauthenticators = helperStatefulCreate("ntlmauthenticator");

        if (!proxy_auth_cache)
            proxy_auth_cache = hash_create((HASHCMP *) strcmp, 7921, hash_string);

        assert(proxy_auth_cache);

        ntlmauthenticators->cmdline = authenticate;

        ntlmauthenticators->n_to_start = authenticateChildren;

        ntlmauthenticators->ipc_type = IPC_STREAM;

        helperStatefulOpenServers(ntlmauthenticators);

        CBDATA_INIT_TYPE(authenticateStateData);
    }
}