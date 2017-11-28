void
Auth::Digest::Config::init(Auth::Config * scheme)
{
    if (authenticateProgram) {
        DigestFieldsInfo = httpHeaderBuildFieldsInfo(DigestAttrs, DIGEST_ENUM_END);
        authenticateDigestNonceSetup();
        authdigest_initialised = 1;

        if (digestauthenticators == NULL)
            digestauthenticators = new helper("digestauthenticator");

        digestauthenticators->cmdline = authenticateProgram;

        digestauthenticators->childs.updateLimits(authenticateChildren);

        digestauthenticators->ipc_type = IPC_STREAM;

        helperOpenServers(digestauthenticators);
    }
}