 */
AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter(const char *name,
                                            ap_out_filter_func filter_func,
                                            ap_init_filter_func filter_init,
                                            ap_filter_type ftype);

/* For httpd-2.2 I suggest replacing the above with
#define ap_register_output_filter(name,ffunc,init,ftype) \
             ap_register_output_filter_protocol(name,ffunc,init,ftype,0)
*/

/**
 * This function is used to register an output filter with the system. 
 * After this registration is performed, then a filter may be added 
 * into the filter chain by using ap_add_output_filter() and simply 
 * specifying the name.  It may also be used as a provider under mod_filter.
 *
 * @param name The name to attach to the filter function
 * @param filter_func The filter function to name
 * @param filter_init The function to call before the filter handlers 
 *                    are invoked
 * @param ftype The type of filter function, either ::AP_FTYPE_CONTENT or
 *              ::AP_FTYPE_CONNECTION
 * @param proto_flags Protocol flags: logical OR of AP_FILTER_PROTO_* bits
 * @see ap_add_output_filter()
 */
AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter_protocol(
                                            const char *name,
                                            ap_out_filter_func filter_func,
                                            ap_init_filter_func filter_init,
                                            ap_filter_type ftype,
                                            unsigned int proto_flags);

/**
 * Adds a named filter into the filter chain on the specified request record.
 * The filter will be installed with the specified context pointer.
 *
 * Filters added in this way will always be placed at the end of the filters
 * that have the same type (thus, the filters have the same order as the
