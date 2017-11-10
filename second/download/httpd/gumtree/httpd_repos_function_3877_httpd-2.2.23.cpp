static apr_status_t dso_cleanup(void *thedso)
{
    apr_dso_handle_t *dso = thedso;

    if (dso->handle != NULL && dlclose(dso->handle) != 0)
        return APR_EINIT;
    dso->handle = NULL;

    return APR_SUCCESS;
}