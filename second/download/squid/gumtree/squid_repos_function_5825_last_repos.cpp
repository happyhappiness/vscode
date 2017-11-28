void
Auth::Basic::Config::init(Auth::Config *)
{
    if (authenticateProgram) {
        authbasic_initialised = 1;

        if (basicauthenticators == NULL)
            basicauthenticators = new helper("basicauthenticator");

        basicauthenticators->cmdline = authenticateProgram;

        basicauthenticators->childs.updateLimits(authenticateChildren);

        basicauthenticators->ipc_type = IPC_STREAM;

        helperOpenServers(basicauthenticators);
    }
}