apr_status_t h2_conn_post(conn_rec *c, h2_worker *worker)
{
    (void)worker;
    
    /* be sure no one messes with this any more */
    memset(c, 0, sizeof(*c)); 
    return APR_SUCCESS;
}