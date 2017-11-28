void
Auth::Negotiate::Config::rotateHelpers()
{
    /* schedule closure of existing helpers */
    if (negotiateauthenticators) {
        helperStatefulShutdown(negotiateauthenticators);
    }

    /* NP: dynamic helper restart will ensure they start up again as needed. */
}