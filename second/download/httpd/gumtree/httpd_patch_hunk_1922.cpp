     ap_filter_func f;
     f.in_func = filter_func;
     return register_filter(name, f, filter_init, ftype,
                            &registered_input_filters);
 }
 
-/* Prepare to make this a #define in 2.2 */
 AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter(const char *name,
                                            ap_out_filter_func filter_func,
                                            ap_init_filter_func filter_init,
                                            ap_filter_type ftype)
 {
     return ap_register_output_filter_protocol(name, filter_func,
-                                              filter_init, ftype, 0) ;
+                                              filter_init, ftype, 0);
 }
+
 AP_DECLARE(ap_filter_rec_t *) ap_register_output_filter_protocol(
                                            const char *name,
                                            ap_out_filter_func filter_func,
                                            ap_init_filter_func filter_init,
                                            ap_filter_type ftype,
                                            unsigned int proto_flags)
