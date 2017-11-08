static void *create_request_dir_config(apr_pool_t *p, char *dummy)
{
    request_dir_conf *new =
        (request_dir_conf *) apr_pcalloc(p, sizeof(request_dir_conf));

    new->keep_body_set = 0; /* unset */
    new->keep_body = 0; /* don't by default */

    return (void *) new;
}