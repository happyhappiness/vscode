static void tell_workers_to_exit(void)
{
    apr_size_t len;
    int i = 0;

    mpm_state = AP_MPMQ_STOPPING;

    for (i = 0 ; i < ap_max_child_assigned; i++){
        len = 4;
        if (apr_sendto(udp_sock, udp_sa, 0, "die!", &len) != APR_SUCCESS)
            break;
    }   
}