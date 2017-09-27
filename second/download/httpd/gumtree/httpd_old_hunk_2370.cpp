 *                         ap_add_loaded_module. Add ap_find_module_short_name
 * 20100723.0 (2.3.7-dev)  Remove ct_output_filters from core rec
 * 20100723.1 (2.3.7-dev)  Added ap_proxy_hashfunc() and hash elements to
 *                         proxy worker structs
 * 20100723.2 (2.3.7-dev)  Add ap_request_has_body()
 * 20100723.3 (2.3.8-dev)  Add ap_check_mpm()
 */

#define MODULE_MAGIC_COOKIE 0x41503234UL /* "AP24" */

#ifndef MODULE_MAGIC_NUMBER_MAJOR
#define MODULE_MAGIC_NUMBER_MAJOR 20100723
#endif
#define MODULE_MAGIC_NUMBER_MINOR 3                     /* 0...n */

/**
 * Determine if the server's current MODULE_MAGIC_NUMBER is at least a
 * specified value.
 *
 * Useful for testing for features.
