
    *accepted = NULL;
    status = apr_accept(&csd, lr->sd, ptrans);
    if (status == APR_SUCCESS) { 
        *accepted = csd;
        apr_os_sock_get(&sockdes, csd);
#ifdef TPF
        if (sockdes == 0) {                  /* 0 is invalid socket for TPF */
            return APR_EINTR;
        }
#endif
        return status;
