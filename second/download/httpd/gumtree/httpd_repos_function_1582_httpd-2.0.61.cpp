static void dumpio_register_hooks(apr_pool_t *p)
{
/*
 * We know that SSL is CONNECTION + 5
 */
  ap_register_output_filter("DUMPIO_OUT", dumpio_output_filter,
	NULL, AP_FTYPE_CONNECTION + 3) ;

  ap_register_input_filter("DUMPIO_IN", dumpio_input_filter,
	NULL, AP_FTYPE_CONNECTION + 3) ;

  ap_hook_pre_connection(dumpio_pre_conn, NULL, NULL, APR_HOOK_MIDDLE);
}