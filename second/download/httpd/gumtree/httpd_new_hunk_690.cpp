
    return;
}

void ssl_io_filter_register(apr_pool_t *p)
{
    ap_register_input_filter  (ssl_io_filter, ssl_io_filter_Input,  NULL, AP_FTYPE_CONNECTION + 5);
    ap_register_output_filter (ssl_io_filter, ssl_io_filter_Output, NULL, AP_FTYPE_CONNECTION + 5);
    return;
}

/*  _________________________________________________________________
**
**  I/O Data Debugging
