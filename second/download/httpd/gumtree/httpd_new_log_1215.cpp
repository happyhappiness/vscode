cache_out_filter_handle = 
        ap_register_output_filter("CACHE_OUT", 
                                  cache_out_filter, 
                                  NULL,
                                  AP_FTYPE_CONTENT_SET-1);