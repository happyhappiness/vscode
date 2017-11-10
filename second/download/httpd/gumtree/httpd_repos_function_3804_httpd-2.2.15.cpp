static apr_status_t dso_cleanup(void *thedso)
{
    apr_dso_handle_t *dso = thedso;

    if (dso->handle > 0 && unload_add_on(dso->handle) < B_NO_ERROR)
        return APR_EINIT;
    dso->handle = -1;

    return APR_SUCCESS;
}