void
Auth::Basic::Config::rotateHelpers()
{
    /* schedule closure of existing helpers */
    if (basicauthenticators) {
        helperShutdown(basicauthenticators);
    }

    /* NP: dynamic helper restart will ensure they start up again as needed. */
}