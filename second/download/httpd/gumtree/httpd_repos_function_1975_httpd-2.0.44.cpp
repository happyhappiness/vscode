static APR_INLINE ap_listen_rec *find_ready_listener(fd_set * main_fds)
{
    ap_listen_rec *lr;
    SOCKET nsd;

    for (lr = head_listener; lr ; lr = lr->next) {
        apr_os_sock_get(&nsd, lr->sd);
	if (FD_ISSET(nsd, main_fds)) {
	    head_listener = lr->next;
            if (head_listener == NULL)
                head_listener = ap_listeners;

	    return (lr);
	}
    }
    return NULL;
}