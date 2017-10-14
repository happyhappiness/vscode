static void show_server_data()
{
    ap_listen_rec *lr;
    module **m;

    printf("%s\n", ap_get_server_version());
    if (ap_my_addrspace && (ap_my_addrspace[0] != 'O') && (ap_my_addrspace[1] != 'S'))
        printf("   Running in address space %s\n", ap_my_addrspace);


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
        }
    }
}