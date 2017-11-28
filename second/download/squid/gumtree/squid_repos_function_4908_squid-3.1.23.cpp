void
ntlmScheme::done()
{
    /* TODO: this should be a Config call. */
    debugs(29, 2, "ntlmScheme::done: shutting down NTLM authentication.");

    if (ntlmauthenticators)
        helperStatefulShutdown(ntlmauthenticators);

    authntlm_initialised = 0;

    if (!shutting_down)
        return;

    if (ntlmauthenticators)
        helperStatefulFree(ntlmauthenticators);

    ntlmauthenticators = NULL;

    debugs(29, 2, "ntlmScheme::done: NTLM authentication Shutdown.");
}