 * @param ftype The type of filter function, either ::AP_FTYPE_CONTENT or ::
 *        AP_FTYPE_CONNECTION
 * @see add_input_filter()
 */
AP_DECLARE(ap_filter_rec_t *) ap_register_input_filter(const char *name,
                                          ap_in_filter_func filter_func,
                                          ap_init_filter_func filter_init,
                                          ap_filter_type ftype);
/**
 * This function is used to register an output filter with the system. 
 * After this registration is performed, then a filter may be added 
 * into the filter chain by using ap_add_output_filter() and simply 
 * specifying the name.
