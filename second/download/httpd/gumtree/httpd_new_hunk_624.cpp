 * @param ftype The type of filter function, either ::AP_FTYPE_CONTENT or
 *              ::AP_FTYPE_CONNECTION
 * @see ap_add_output_filter()
 */
AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter(const char *name,
                                            ap_out_filter_func filter_func,
                                            ap_init_filter_func filter_init,
                                            ap_filter_type ftype);

/**
 * Adds a named filter into the filter chain on the specified request record.
 * The filter will be installed with the specified context pointer.
 *
