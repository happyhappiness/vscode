 */
AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter(const char *name,
                                            ap_out_filter_func filter_func,
                                            ap_init_filter_func filter_init,
                                            ap_filter_type ftype);

/**
 * Adds a named filter into the filter chain on the specified request record.
 * The filter will be installed with the specified context pointer.
 *
 * Filters added in this way will always be placed at the end of the filters
 * that have the same type (thus, the filters have the same order as the
