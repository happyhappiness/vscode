static apr_status_t dso_cleanup(void *thedso)
{
    apr_dso_handle_t *dso = thedso;

    if (dso->handle == NULL)
        return APR_SUCCESS;

#if defined(DSO_USE_SHL)
    shl_unload((shl_t)dso->handle);
#elif defined(DSO_USE_DYLD)
    if (dso->handle != DYLD_LIBRARY_HANDLE) {
        NSUnLinkModule(dso->handle, FALSE);
    }
#elif defined(DSO_USE_DLFCN)
    if (dlclose(dso->handle) != 0)
        return APR_EINIT;
#endif
    dso->handle = NULL;

    return APR_SUCCESS;
}