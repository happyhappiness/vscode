 /* For httpd-?.? I suggest replacing the above with
 #define ap_register_output_filter(name,ffunc,init,ftype) \
              ap_register_output_filter_protocol(name,ffunc,init,ftype,0)
 */
 
 /**
- * This function is used to register an output filter with the system. 
- * After this registration is performed, then a filter may be added 
+ * This function is used to register an output filter with the system.
+ * After this registration is performed, then a filter may be added
  * directly to the filter chain by using ap_add_output_filter() and
  * simply specifying the name, or as a provider under mod_filter.
  *
  * @param name The name to attach to the filter function
  * @param filter_func The filter function to name
- * @param filter_init The function to call before the filter handlers 
+ * @param filter_init The function to call before the filter handlers
  *                    are invoked
- * @param ftype The type of filter function, either ::AP_FTYPE_CONTENT or
+ * @param ftype The type of filter function, either ::AP_FTYPE_CONTENT_SET or
  *              ::AP_FTYPE_CONNECTION
  * @param proto_flags Protocol flags: logical OR of AP_FILTER_PROTO_* bits
  * @return the filter rec
  * @see ap_add_output_filter()
  */
 AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter_protocol(
