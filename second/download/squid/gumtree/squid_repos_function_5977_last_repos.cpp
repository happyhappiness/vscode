void
Auth::Digest::Config::done()
{
    Auth::Config::done();

    authdigest_initialised = 0;

    if (digestauthenticators)
        helperShutdown(digestauthenticators);

    if (!shutting_down)
        return;

    delete digestauthenticators;
    digestauthenticators = NULL;

    if (authenticateProgram)
        wordlistDestroy(&authenticateProgram);
}