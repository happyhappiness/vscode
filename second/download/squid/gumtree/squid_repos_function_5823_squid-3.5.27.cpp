void
Auth::Basic::Config::done()
{
    Auth::Config::done();

    authbasic_initialised = 0;

    if (basicauthenticators) {
        helperShutdown(basicauthenticators);
    }

    delete basicauthenticators;
    basicauthenticators = NULL;

    if (authenticateProgram)
        wordlistDestroy(&authenticateProgram);
}