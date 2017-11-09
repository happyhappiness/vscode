static void add_push(apr_pool_t *pool, h2_config *conf, h2_push_res *push)
{
    h2_push_res *new;
    if (!conf->push_list) {
        conf->push_list = apr_array_make(pool, 10, sizeof(*push));
    }
    new = apr_array_push(conf->push_list);
    new->uri_ref = push->uri_ref;
    new->critical = push->critical;
}