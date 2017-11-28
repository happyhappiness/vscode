void
Auth::Digest::Config::rotateHelpers()
{
    /* schedule closure of existing helpers */
    if (digestauthenticators) {
        helperShutdown(digestauthenticators);
    }

    /* NP: dynamic helper restart will ensure they start up again as needed. */
}