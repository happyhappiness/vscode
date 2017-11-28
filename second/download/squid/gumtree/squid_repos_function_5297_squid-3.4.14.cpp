void
Auth::Negotiate::Config::done()
{
    authnegotiate_initialised = 0;

    if (negotiateauthenticators) {
        helperStatefulShutdown(negotiateauthenticators);
    }

    if (!shutting_down)
        return;

    delete negotiateauthenticators;
    negotiateauthenticators = NULL;

    if (authenticateProgram)
        wordlistDestroy(&authenticateProgram);

    debugs(29, DBG_IMPORTANT, "Reconfigure: Negotiate authentication configuration cleared.");
}