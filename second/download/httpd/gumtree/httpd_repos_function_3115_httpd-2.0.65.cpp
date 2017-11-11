static apr_status_t dso_cleanup(void *thedso)
{
    apr_dso_handle_t *dso = thedso;

    if (dso->handle != NULL && !FreeLibrary(dso->handle)) {
        return apr_get_os_error();
    }
    dso->handle = NULL;

    return APR_SUCCESS;
}