                                               request_rec *r, conn_rec *c);

/**
 * Variant of ap_add_output_filter() that accepts a registered filter handle
 * (as returned by ap_register_output_filter()) rather than a filter name
 *
 * @param name The filter to add
 * @param r The request to add this filter for (or NULL if it isn't associated with a request)
 * @param c The connection to add the fillter for
 */
AP_DECLARE(ap_filter_t *) ap_add_output_filter_handle(ap_filter_rec_t *f,
                                                      void *ctx,
                                                      request_rec *r,
