static const char *dbd_freetds_error(apr_dbd_t *sql, int n)
{
    /* XXX this doesn't seem to exist in the API ??? */
    return apr_psprintf(sql->pool, "Error %d", sql->err);
}