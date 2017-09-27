  * After this registration is performed, then a filter may be added 
  * into the filter chain by using ap_add_output_filter() and simply 
  * specifying the name.
  *
  * @param name The name to attach to the filter function
  * @param filter_func The filter function to name
+ * @param filter_init The function to call before the filter handlers 
+ *                    are invoked
  * @param ftype The type of filter function, either ::AP_FTYPE_CONTENT or
  *              ::AP_FTYPE_CONNECTION
  * @see ap_add_output_filter()
  */
 AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter(const char *name,
                                             ap_out_filter_func filter_func,
