void
AuthDigestConfig::init(AuthConfig * scheme)
{
    if (authenticate) {
        DigestFieldsInfo = httpHeaderBuildFieldsInfo(DigestAttrs, DIGEST_ENUM_END);
        authenticateDigestNonceSetup();
        authdigest_initialised = 1;

        if (digestauthenticators == NULL)
            digestauthenticators = helperCreate("digestauthenticator");

        digestauthenticators->cmdline = authenticate;

        digestauthenticators->n_to_start = authenticateChildren;

        digestauthenticators->ipc_type = IPC_STREAM;

        helperOpenServers(digestauthenticators);

        CBDATA_INIT_TYPE(DigestAuthenticateStateData);
    }
}