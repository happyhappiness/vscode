    /* Display listening ports */
    printf("   Listening on port(s):");
    lr = ap_listeners;
    do {
       printf(" %d", lr->bind_addr->port);
       lr = lr->next;
    } while(lr && lr != ap_listeners);

    /* Display dynamic modules loaded */
    printf("\n");
    for (m = ap_loaded_modules; *m != NULL; m++) {
        if (((module*)*m)->dynamic_load_handle) {
            printf("   Loaded dynamic module %s\n", ((module*)*m)->name);
