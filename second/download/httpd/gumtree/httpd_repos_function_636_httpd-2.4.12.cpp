static int generate_log_id(const conn_rec *c, const request_rec *r,
                           const char **id)
{
    /* we do not care about connection ids */
    if (r == NULL)
        return DECLINED;

    /* XXX: do we need special handling for internal redirects? */

    /* if set_unique_id() has been called for this request, use it */
    *id = apr_table_get(r->subprocess_env, "UNIQUE_ID");

    if (!*id)
        *id = gen_unique_id(r);
    return OK;
}