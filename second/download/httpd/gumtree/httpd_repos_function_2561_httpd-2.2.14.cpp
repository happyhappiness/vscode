static apr_status_t datum_cleanup(void *dptr)
{
    if (dptr)
        free(dptr);

    return APR_SUCCESS;
}