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
 * specifying the name.  It may also be used as a provider under mod_filter.
 * This is (equivalent to) ap_register_output_filter_protocol with
 * proto_flags=0, and is retained for back-compatibility with 2.0 modules.
 *
 * @param name The name to attach to the filter function
 * @param filter_func The filter function to name
 * @param filter_init The function to call before the filter handlers 
 *                    are invoked
 * @param ftype The type of filter function, either ::AP_FTYPE_CONTENT or
