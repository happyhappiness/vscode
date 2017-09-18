            else if ((pollevent & APR_POLLERR) || (pollevent & APR_POLLHUP))
		break;


            apr_poll_revents_get(&pollevent, client_socket, pollfd);
            if (pollevent & APR_POLLIN) {
/*		ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: CONNECT: client was set");*/
                nbytes = sizeof(buffer);
                if (apr_recv(client_socket, buffer, &nbytes) == APR_SUCCESS) {
                    o = 0;
                    i = nbytes;
                    while(i > 0)
