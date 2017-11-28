void
Auth::Ntlm::Config::done()
{
    authntlm_initialised = 0;

    if (ntlmauthenticators) {
        helperStatefulShutdown(ntlmauthenticators);
    }

    if (!shutting_down)
        return;

    delete ntlmauthenticators;
    ntlmauthenticators = NULL;

    if (authenticateProgram)
        wordlistDestroy(&authenticateProgram);

    debugs(29, DBG_IMPORTANT, "Reconfigure: NTLM authentication configuration cleared.");
}