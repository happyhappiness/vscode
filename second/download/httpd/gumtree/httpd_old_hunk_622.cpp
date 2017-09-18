 *
 * Callbacks are associated with a filter definition, which is specified
 * by name. See ap_register_input_filter() and ap_register_output_filter()
 * for setting the association between a name for a filter and its 
 * associated callback (and other information).
 *
 * The *bucket structure (and all those referenced by ->next and ->prev)
 * should be considered "const". The filter is allowed to modify the
 * next/prev to insert/remove/replace elements in the bucket list, but
 * the types and values of the individual buckets should not be altered.
 *
 * The return value of a filter should be an APR status value.
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

typedef union ap_filter_func {
    ap_out_filter_func out_func;
    ap_in_filter_func in_func;
} ap_filter_func;

