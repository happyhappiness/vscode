void
Auth::Digest::Config::init(Auth::Config *)
{
    if (authenticateProgram) {
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