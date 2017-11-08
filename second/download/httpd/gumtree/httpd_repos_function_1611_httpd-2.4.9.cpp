static apr_status_t unload_module(void *data)
{
    ap_module_symbol_t *modi = (ap_module_symbol_t*)data;

    /* only unload if module information is still existing */
    if (modi->modp == NULL)
        return APR_SUCCESS;

    /* remove the module pointer from the core structure */
    ap_remove_loaded_module(modi->modp);

    /* destroy the module information */
    modi->modp = NULL;
    modi->name = NULL;
    return APR_SUCCESS;
}