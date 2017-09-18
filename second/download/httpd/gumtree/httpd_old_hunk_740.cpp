    else {
        frec = apr_palloc(FILTER_POOL, sizeof(*frec));
        node->frec = frec;
        frec->name = normalized_name;
    }
    frec->filter_func = filter_func;
    frec->ftype = ftype;
    
    apr_pool_cleanup_register(FILTER_POOL, NULL, filter_cleanup, 
                              apr_pool_cleanup_null);
    return frec;
}

AP_DECLARE(ap_filter_rec_t *) ap_register_input_filter(const char *name,
                                          ap_in_filter_func filter_func,
                                          ap_filter_type ftype)
{
    ap_filter_func f;
    f.in_func = filter_func;
    return register_filter(name, f, ftype, &registered_input_filters);
}                                                                    

AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter(const char *name,
                                           ap_out_filter_func filter_func,
                                           ap_filter_type ftype)
{
    ap_filter_func f;
    f.out_func = filter_func;
    return register_filter(name, f, ftype, &registered_output_filters);
}

static ap_filter_t *add_any_filter_handle(ap_filter_rec_t *frec, void *ctx, 
                                          request_rec *r, conn_rec *c, 
                                          ap_filter_t **r_filters,
                                          ap_filter_t **p_filters,
