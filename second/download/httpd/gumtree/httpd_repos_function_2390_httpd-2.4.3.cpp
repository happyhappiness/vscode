static void *create_session_cookie_dir_config(apr_pool_t * p, char *dummy)
{
    session_cookie_dir_conf *new =
    (session_cookie_dir_conf *) apr_pcalloc(p, sizeof(session_cookie_dir_conf));

    return (void *) new;
}