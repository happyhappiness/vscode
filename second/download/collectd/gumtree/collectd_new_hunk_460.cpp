    for (i = 0; i < nr_interface_devices; ++i)
        fprintf (stderr, "interface device %d %s:%s\n",
                 i, virDomainGetName (interface_devices[i].dom),
                 interface_devices[i].path);
#endif

    /* Get CPU usage, memory, VCPU usage for each domain. */
    for (i = 0; i < nr_domains; ++i) {
        virDomainInfo info;
        virVcpuInfoPtr vinfo = NULL;
        int status;
        int j;

