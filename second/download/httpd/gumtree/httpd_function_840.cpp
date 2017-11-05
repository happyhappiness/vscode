static void show_mpm_settings(void)
{
    int mpm_query_info;
    apr_status_t retval;

    printf("Server MPM:     %s\n", ap_show_mpm());

    retval = ap_mpm_query(AP_MPMQ_IS_THREADED, &mpm_query_info);

    if (retval == APR_SUCCESS) {
        printf("  threaded:     ");

        if (mpm_query_info == AP_MPMQ_DYNAMIC) {
            printf("yes (variable thread count)\n");
        }
        else if (mpm_query_info == AP_MPMQ_STATIC) {
            printf("yes (fixed thread count)\n");
        }
        else {
            printf("no\n");
        }
    }

    retval = ap_mpm_query(AP_MPMQ_IS_FORKED, &mpm_query_info);

    if (retval == APR_SUCCESS) {
        printf("    forked:     ");

        if (mpm_query_info == AP_MPMQ_DYNAMIC) {
            printf("yes (variable process count)\n");
        }
        else if (mpm_query_info == AP_MPMQ_STATIC) {
            printf("yes (fixed process count)\n");
        }
        else {
            printf("no\n");
        }
    }
}