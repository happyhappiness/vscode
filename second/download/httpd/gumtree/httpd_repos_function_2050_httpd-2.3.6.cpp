static void *merge_buffer_config(apr_pool_t *p, void *basev, void *addv) {
    buffer_conf *new = (buffer_conf *) apr_pcalloc(p, sizeof(buffer_conf));
    buffer_conf *add = (buffer_conf *) addv;
    buffer_conf *base = (buffer_conf *) basev;

    new->size = (add->size_set == 0) ? base->size : add->size;
    new->size_set = add->size_set || base->size_set;

    return new;
}