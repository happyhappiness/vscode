void
negotiateScheme::done()
{
    /* TODO: this should be a Config call. */
    debugs(29, 2, "negotiateScheme::done: shutting down Negotiate authentication.");

    if (negotiateauthenticators)
        helperStatefulShutdown(negotiateauthenticators);

    authnegotiate_initialised = 0;

    if (!shutting_down)
        return;

    if (negotiateauthenticators)
        helperStatefulFree(negotiateauthenticators);

    negotiateauthenticators = NULL;

    debugs(29, 2, "negotiateScheme::done: Negotiate authentication Shutdown.");
}