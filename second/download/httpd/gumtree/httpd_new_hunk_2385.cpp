 * @param c The connection to add this filter for
 * @note If adding a connection-level output filter (i.e. where the type
 * is >= AP_FTYPE_CONNECTION) during processing of a request, the request
 * object r must be passed in to ensure the filter chains are modified
 * correctly.  f->r will still be initialized as NULL in the new filter.
 */
AP_DECLARE(ap_filter_t *) ap_add_output_filter(const char *name, void *ctx,
                                               request_rec *r, conn_rec *c);

/**
 * Variant of ap_add_output_filter() that accepts a registered filter handle
 * (as returned by ap_register_output_filter()) rather than a filter name
 *
