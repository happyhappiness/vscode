static apr_status_t cleanup_isapi(void *isa_)
{
    isapi_loaded* isa = (isapi_loaded*) isa_;

    /* We must force the module to unload, we are about
     * to lose the isapi structure's allocation entirely.
     */
    return isapi_unload(isa, 1);
}