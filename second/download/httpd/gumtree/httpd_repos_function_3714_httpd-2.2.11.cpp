static apr_status_t dso_cleanup(void *thedso)
{
    apr_dso_handle_t *dso = thedso;
    int rc;

    if (dso->handle == 0)
        return APR_SUCCESS;
       
    rc = DosFreeModule(dso->handle);

    if (rc == 0)
        dso->handle = 0;

    return APR_FROM_OS_ERROR(rc);
}