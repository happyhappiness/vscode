 *
 * Callbacks are associated with a filter definition, which is specified
 * by name. See ap_register_input_filter() and ap_register_output_filter()
 * for setting the association between a name for a filter and its 
 * associated callback (and other information).
 *
 * If the initialization function argument passed to the registration
 * functions is non-NULL, it will be called iff the filter is in the input
 * or output filter chains and before any data is generated to allow the
 * filter to prepare for processing.
 *
 * The *bucket structure (and all those referenced by ->next and ->prev)
 * should be considered "const". The filter is allowed to modify the
 * next/prev to insert/remove/replace elements in the bucket list, but
 * the types and values of the individual buckets should not be altered.
 *
 * For the input and output filters, the return value of a filter should be
 * an APR status value.  For the init function, the return value should
 * be an HTTP error code or OK if it was successful.
 * 
 * @ingroup filter
 * @{
 */
typedef apr_status_t (*ap_out_filter_func)(ap_filter_t *f,
                                           apr_bucket_brigade *b);
typedef apr_status_t (*ap_in_filter_func)(ap_filter_t *f,
                                          apr_bucket_brigade *b, 
                                          ap_input_mode_t mode,
                                          apr_read_type_e block,
                                          apr_off_t readbytes);
typedef int (*ap_init_filter_func)(ap_filter_t *f);

typedef union ap_filter_func {
    ap_out_filter_func out_func;
    ap_in_filter_func in_func;
} ap_filter_func;

