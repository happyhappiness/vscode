                LogTime(), PROGRAM, gai_strerror(rc));
        return NULL;
    }
    hres_list = hres;
    count = 0;
    while (hres_list) {
        ++count;
        hres_list = hres_list->ai_next;
    }
    rc = getnameinfo(hres->ai_addr, hres->ai_addrlen, hostname,
                     sizeof(hostname), NULL, 0, 0);
    if (rc != 0) {
        fprintf(stderr,
