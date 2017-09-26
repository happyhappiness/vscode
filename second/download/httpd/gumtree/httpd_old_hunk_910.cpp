	 */

	/* Lock around "accept", if necessary */
	SAFE_ACCEPT(accept_mutex_on());

        if (num_listensocks == 1) {
            offset = 0;
        }
        else {
            /* multiple listening sockets - need to poll */
	    for (;;) {
                apr_status_t ret;
                apr_int32_t n;

                ret = apr_poll(pollset, num_listensocks, &n, -1);
                if (ret != APR_SUCCESS) {
                    if (APR_STATUS_IS_EINTR(ret)) {
                        continue;
                    }
    	            /* Single Unix documents select as returning errnos
    	             * EBADF, EINTR, and EINVAL... and in none of those
    	             * cases does it make sense to continue.  In fact
    	             * on Linux 2.0.x we seem to end up with EFAULT
    	             * occasionally, and we'd loop forever due to it.
    	             */
    	            ap_log_error(APLOG_MARK, APLOG_ERR, ret, ap_server_conf,
                             "apr_poll: (listen)");
    	            clean_child_exit(1);
                }
                /* find a listener */
                curr_pollfd = last_pollfd;
                do {
                    curr_pollfd++;
                    if (curr_pollfd >= num_listensocks) {
                        curr_pollfd = 0;
                    }
                    /* XXX: Should we check for POLLERR? */
                    if (pollset[curr_pollfd].rtnevents & APR_POLLIN) {
                        last_pollfd = curr_pollfd;
                        offset = curr_pollfd;
                        goto got_fd;
                    }
                } while (curr_pollfd != last_pollfd);

                continue;
            }
        }
    got_fd:
	/* if we accept() something we don't want to die, so we have to
	 * defer the exit
	 */
        status = listensocks[offset].accept_func(&csd, 
                                                 &listensocks[offset], ptrans);
        SAFE_ACCEPT(accept_mutex_off());	/* unlock after "accept" */

        if (status == APR_EGENERAL) {
            /* resource shortage or should-not-occur occured */
            clean_child_exit(1);
        }
        else if (status != APR_SUCCESS) {
