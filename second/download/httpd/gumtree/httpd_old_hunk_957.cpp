                                          ap_filter_type ftype)
{
    ap_filter_func f;
    f.in_func = filter_func;
    return register_filter(name, f, filter_init, ftype,
                           &registered_input_filters);
}                                                                    

AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter(const char *name,
                                           ap_out_filter_func filter_func,
                                           ap_init_filter_func filter_init,
                                           ap_filter_type ftype)
{
    ap_filter_func f;
    f.out_func = filter_func;
    return register_filter(name, f, filter_init, ftype,
                           &registered_output_filters);
}

static ap_filter_t *add_any_filter_handle(ap_filter_rec_t *frec, void *ctx, 
                                          request_rec *r, conn_rec *c, 
                                          ap_filter_t **r_filters,
                                          ap_filter_t **p_filters,
                                          ap_filter_t **c_filters)
{
    apr_pool_t* p = r ? r->pool : c->pool;
    ap_filter_t *f = apr_palloc(p, sizeof(*f));
