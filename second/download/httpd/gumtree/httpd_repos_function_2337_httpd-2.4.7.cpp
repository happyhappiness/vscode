static void *merge_request_dir_config(apr_pool_t *p, void *basev, void *addv)
{
    request_dir_conf *new = (request_dir_conf *) apr_pcalloc(p, sizeof(request_dir_conf));
    request_dir_conf *add = (request_dir_conf *) addv;
    request_dir_conf *base = (request_dir_conf *) basev;

    new->keep_body = (add->keep_body_set == 0) ? base->keep_body : add->keep_body;
    new->keep_body_set = add->keep_body_set || base->keep_body_set;

    return new;
}