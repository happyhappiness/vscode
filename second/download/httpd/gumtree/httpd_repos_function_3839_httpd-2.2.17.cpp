static apr_status_t dso_cleanup(void *thedso)
{
    apr_dso_handle_t *dso = thedso;
    sym_list *symbol = NULL;
    void *NLMHandle = getnlmhandle();

    if (dso->handle == NULL)
        return APR_SUCCESS;

    if (dso->symbols != NULL) {
        symbol = dso->symbols;
        while (symbol) {
            UnImportPublicObject(NLMHandle, symbol->symbol);
            symbol = symbol->next;
        }
    }

    if (dlclose(dso->handle) != 0)
        return APR_EINIT;

    dso->handle = NULL;
    dso->symbols = NULL;
    dso->path = NULL;

    return APR_SUCCESS;
}