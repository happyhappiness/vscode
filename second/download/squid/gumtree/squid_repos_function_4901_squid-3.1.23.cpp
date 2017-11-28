void
AuthBasicConfig::init(AuthConfig * scheme)
{
    if (authenticate) {
        authbasic_initialised = 1;

        if (basicauthenticators == NULL)
            basicauthenticators = helperCreate("basicauthenticator");

        basicauthenticators->cmdline = authenticate;

        basicauthenticators->n_to_start = authenticateChildren;

        basicauthenticators->concurrency = authenticateConcurrency;

        basicauthenticators->ipc_type = IPC_STREAM;

        helperOpenServers(basicauthenticators);

        CBDATA_INIT_TYPE(AuthenticateStateData);
    }
}