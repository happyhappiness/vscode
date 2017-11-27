            return -1;
        }
        last_refresh = t;
    }

#if 0
    for (int i = 0; i < nr_domains; ++i)
        fprintf (stderr, "domain %s\n", virDomainGetName (domains[i]));
    for (int i = 0; i < nr_block_devices; ++i)
        fprintf  (stderr, "block device %d %s:%s\n",
                  i, virDomainGetName (block_devices[i].dom),
                  block_devices[i].path);
    for (int i = 0; i < nr_interface_devices; ++i)
        fprintf (stderr, "interface device %d %s:%s\n",
                 i, virDomainGetName (interface_devices[i].dom),
                 interface_devices[i].path);
#endif

    /* Get CPU usage, memory, VCPU usage for each domain. */
    for (int i = 0; i < nr_domains; ++i) {
        virDomainInfo info;
        virVcpuInfoPtr vinfo = NULL;
        virDomainMemoryStatPtr minfo = NULL;
        int status;

        status = virDomainGetInfo (domains[i], &info);
        if (status != 0)
        {
            ERROR (PLUGIN_NAME " plugin: virDomainGetInfo failed with status %i.",
                    status);
