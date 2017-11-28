void
basicScheme::done()
{
    /* TODO: this should be a Config call. */

    if (basicauthenticators)
        helperShutdown(basicauthenticators);

    authbasic_initialised = 0;

    if (!shutting_down)
        return;

    if (basicauthenticators)
        helperFree(basicauthenticators);

    basicauthenticators = NULL;

    /* XXX Reinstate auth shutdown for dynamic schemes? */
    debugs(29, DBG_CRITICAL, HERE << "Basic authentication Shutdown.");
}