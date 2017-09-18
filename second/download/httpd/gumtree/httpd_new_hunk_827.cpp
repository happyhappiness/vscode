        return my_addr;
    }

    hep = gethostbyname(w);

    if ((!hep) || (hep->h_addrtype != AF_INET || !hep->h_addr_list[0])) {
        /* XXX Should be echoing by r_errno the actual failure, no? 
         * ap_log_error would be good here.
         */
        fprintf(stderr, "Cannot resolve host name %s --- exiting!\n", w);
        exit(1);
    }

    if (hep->h_addr_list[1]) {
        fprintf(stderr, "Host %s has multiple addresses ---\n", w);
