static void *make_cookie_log_state(apr_pool_t *p, server_rec *s)
{
    cookie_log_state *cls =
    (cookie_log_state *) apr_palloc(p, sizeof(cookie_log_state));

    cls->expires = 0;

    return (void *) cls;
}