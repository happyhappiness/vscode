 * Add a filter to the current request.  Filters are added in a FIFO manner.
 * The first filter added will be the first filter called.
 * @param name The name of the filter to add
 * @param ctx Context data to set in the filter
 * @param r The request to add this filter for (or NULL if it isn't associated with a request)
 * @param c The connection to add this filter for
 */
AP_DECLARE(ap_filter_t *) ap_add_output_filter(const char *name, void *ctx, 
                                               request_rec *r, conn_rec *c);

/**
 * Variant of ap_add_output_filter() that accepts a registered filter handle
 * (as returned by ap_register_output_filter()) rather than a filter name
 *
 * @param f The filter handle to add
 * @param r The request to add this filter for (or NULL if it isn't associated with a request)
 * @param c The connection to add the fillter for
 */
AP_DECLARE(ap_filter_t *) ap_add_output_filter_handle(ap_filter_rec_t *f,
                                                      void *ctx,
                                                      request_rec *r,
                                                      conn_rec *c);

