ap_old_write_func =
        ap_register_output_filter("OLD_WRITE", ap_old_write_filter,
                                  NULL, AP_FTYPE_RESOURCE - 10);