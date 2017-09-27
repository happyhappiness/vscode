
static void show_server_data()
{
    ap_listen_rec *lr;
    module **m;

    printf("%s\n", ap_get_server_description());
    if (ap_my_addrspace && (ap_my_addrspace[0] != 'O') && (ap_my_addrspace[1] != 'S'))
        printf("   Running in address space %s\n", ap_my_addrspace);


    /* Display listening ports */
    printf("   Listening on port(s):");
