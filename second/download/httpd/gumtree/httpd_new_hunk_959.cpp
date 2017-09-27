}

AP_DECLARE(ap_filter_t *) ap_add_input_filter(const char *name, void *ctx,
                                              request_rec *r, conn_rec *c)
{
    return add_any_filter(name, ctx, r, c, registered_input_filters,
                          r ? &r->input_filters : NULL,
                          r ? &r->proto_input_filters : NULL, &c->input_filters);
}

AP_DECLARE(ap_filter_t *) ap_add_input_filter_handle(ap_filter_rec_t *f,
                                                     void *ctx,
                                                     request_rec *r,
                                                     conn_rec *c)
{
    return add_any_filter_handle(f, ctx, r, c, r ? &r->input_filters : NULL,
                                 r ? &r->proto_input_filters : NULL,
                                 &c->input_filters);
}

AP_DECLARE(ap_filter_t *) ap_add_output_filter(const char *name, void *ctx,
                                               request_rec *r, conn_rec *c)
{
    return add_any_filter(name, ctx, r, c, registered_output_filters,
                          r ? &r->output_filters : NULL,
                          r ? &r->proto_output_filters : NULL, &c->output_filters);
}

AP_DECLARE(ap_filter_t *) ap_add_output_filter_handle(ap_filter_rec_t *f,
                                                      void *ctx,
                                                      request_rec *r,
