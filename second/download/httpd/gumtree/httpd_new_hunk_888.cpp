              continue;
         }
         perform_idle_server_maintenance();
    }
}

/* This is called to not only setup and run for the initial time, but also
 * when we've asked for a restart. This means it must be able to handle both
 * situations. It also means that when we exit here we should have tidied
 * up after ourselves fully.
 */
int ap_mpm_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
{
    int remaining_threads_to_start, i,j;
    apr_status_t rv;
    ap_listen_rec *lr;
    pconf = _pconf;
    ap_server_conf = s;

    /* Increase the available pool of fd's.  This code from
     * Joe Kloss <joek@be.com>
     */
    if( FD_SETSIZE > 128 && (i = _kset_fd_limit_( 128 )) < 0 ){
        ap_log_error(APLOG_MARK, APLOG_ERR, i, s,
            "could not set FD_SETSIZE (_kset_fd_limit_ failed)");
    }

    /* BeOS R5 doesn't support pipes on select() calls, so we use a
     * UDP socket as these are supported in both R5 and BONE.  If we only cared
     * about BONE we'd use a pipe, but there it is.
     * As we have UDP support in APR, now use the APR functions and check all the
     * return values...
     */
    if (apr_sockaddr_info_get(&udp_sa, "127.0.0.1", APR_UNSPEC, 7772, 0, _pconf)
        != APR_SUCCESS){
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, s,
            "couldn't create control socket information, shutting down");
        return 1;
    }
    if (apr_socket_create(&udp_sock, udp_sa->family, SOCK_DGRAM, 0,
                      _pconf) != APR_SUCCESS){
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, s,
            "couldn't create control socket, shutting down");
        return 1;
    }
    if (apr_socket_bind(udp_sock, udp_sa) != APR_SUCCESS){
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, s,
            "couldn't bind UDP socket!");
        return 1;
    }

    if ((num_listening_sockets = ap_setup_listeners(ap_server_conf)) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s,
            "no listening sockets available, shutting down");
        return 1;
    }

    ap_log_pid(pconf, ap_pid_fname);

    /*
     * Create our locks...
     */

    /* accept_mutex
     * used to lock around select so we only have one thread
     * in select at a time
     */
    rv = apr_thread_mutex_create(&accept_mutex, 0, pconf);
    if (rv != APR_SUCCESS) {
