static apr_status_t isapi_unload(isapi_loaded *isa, int force)
{
    /* All done with the DLL... get rid of it...
     *
     * If optionally cached, and we weren't asked to force the unload,
     * pass HSE_TERM_ADVISORY_UNLOAD, and if it returns 1, unload,
     * otherwise, leave it alone (it didn't choose to cooperate.)
     */
    if (!isa->handle) {
        return APR_SUCCESS;
    }
    if (isa->TerminateExtension) {
        if (force) {
            (*isa->TerminateExtension)(HSE_TERM_MUST_UNLOAD);
        }
        else if (!(*isa->TerminateExtension)(HSE_TERM_ADVISORY_UNLOAD)) {
            return APR_EGENERAL;
        }
    }
    apr_dso_unload(isa->handle);
    isa->handle = NULL;
    return APR_SUCCESS;
}