void
Auth::Ntlm::Config::rotateHelpers()
{
    /* schedule closure of existing helpers */
    if (ntlmauthenticators) {
        helperStatefulShutdown(ntlmauthenticators);
    }

    /* NP: dynamic helper restart will ensure they start up again as needed. */
}