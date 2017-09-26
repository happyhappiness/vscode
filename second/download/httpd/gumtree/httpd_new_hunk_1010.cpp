                                          ap_filter_type ftype)
{
    ap_filter_func f;
    f.in_func = filter_func;
    return register_filter(name, f, filter_init, ftype,
                           &registered_input_filters);
}

/* Prepare to make this a #define in 2.2 */
AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter(const char *name,
                                           ap_out_filter_func filter_func,
                                           ap_init_filter_func filter_init,
                                           ap_filter_type ftype)
{
    return ap_register_output_filter_protocol(name, filter_func,
                                              filter_init, ftype, 0) ;
}
AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter_protocol(
                                           const char *name,
                                           ap_out_filter_func filter_func,
                                           ap_init_filter_func filter_init,
                                           ap_filter_type ftype,
                                           unsigned int proto_flags)
{
    ap_filter_rec_t* ret ;
    ap_filter_func f;
    f.out_func = filter_func;
    ret = register_filter(name, f, filter_init, ftype,
                          &registered_output_filters);
    ret->proto_flags = proto_flags ;
    return ret ;
}

static ap_filter_t *add_any_filter_handle(ap_filter_rec_t *frec, void *ctx,
                                          request_rec *r, conn_rec *c,
                                          ap_filter_t **r_filters,
                                          ap_filter_t **p_filters,
                                          ap_filter_t **c_filters)
{
    apr_pool_t* p = r ? r->pool : c->pool;
    ap_filter_t *f = apr_palloc(p, sizeof(*f));
