static int dbd_freetds_select_db(apr_pool_t *pool, apr_dbd_t *handle,
                               const char *name)
{
    /* ouch, it's declared int.  But we can use APR 0/nonzero */
    return (dbuse(handle->proc, (char*)name) == SUCCEED) ? APR_SUCCESS : APR_EGENERAL;
}