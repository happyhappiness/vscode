static int
lv_read (void)
{
    time_t t;
    int i;

    if (conn == NULL) {
        ERROR ("libvirt plugin: Not connected. Use Connection in "
                "config file to supply connection URI.  For more information "
                "see <http://libvirt.org/uri.html>");
        return -1;
    }

    time (&t);

    /* Need to refresh domain or device lists? */
    if ((last_refresh == (time_t) 0) ||
            ((interval > 0) && ((last_refresh + interval) <= t))) {
        if (refresh_lists () != 0)
            return -1;
        last_refresh = t;
    }

#if 0
    for (i = 0; i < nr_domains; ++i)
        fprintf (stderr, "domain %s\n", virDomainGetName (domains[i]));
    for (i = 0; i < nr_block_devices; ++i)
        fprintf  (stderr, "block device %d %s:%s\n",
                  i, virDomainGetName (block_devices[i].dom),
                  block_devices[i].path);
    for (i = 0; i < nr_interface_devices; ++i)
        fprintf (stderr, "interface device %d %s:%s\n",
                 i, virDomainGetName (interface_devices[i].dom),
                 interface_devices[i].path);
#endif

    /* Get CPU usage, VCPU usage for each domain. */
    for (i = 0; i < nr_domains; ++i) {
        virDomainInfo info;
        virVcpuInfoPtr vinfo = NULL;
        int j;

        if (virDomainGetInfo (domains[i], &info) != 0)
            continue;

        cpu_submit (info.cpuTime, t, domains[i], "virt_cpu_total");

        vinfo = malloc (info.nrVirtCpu * sizeof vinfo[0]);
        if (vinfo == NULL) {
            ERROR ("libvirt plugin: malloc failed.");
            continue;
        }

        if (virDomainGetVcpus (domains[i], vinfo, info.nrVirtCpu,
                    NULL, 0) != 0) {
            free (vinfo);
            continue;
        }

        for (j = 0; j < info.nrVirtCpu; ++j)
            vcpu_submit (vinfo[j].cpuTime,
                    t, domains[i], vinfo[j].number, "virt_vcpu");

        free (vinfo);
    }

    /* Get block device stats for each domain. */
    for (i = 0; i < nr_block_devices; ++i) {
        struct _virDomainBlockStats stats;

        if (virDomainBlockStats (block_devices[i].dom, block_devices[i].path,
                    &stats, sizeof stats) != 0)
            continue;

        if ((stats.rd_req != -1) && (stats.wr_req != -1))
            submit_counter2 ("disk_ops",
                    (counter_t) stats.rd_req, (counter_t) stats.wr_req,
                    t, block_devices[i].dom, block_devices[i].path);

        if ((stats.rd_bytes != -1) && (stats.wr_bytes != -1))
            submit_counter2 ("disk_octets",
                    (counter_t) stats.rd_bytes, (counter_t) stats.wr_bytes,
                    t, block_devices[i].dom, block_devices[i].path);
    } /* for (nr_block_devices) */

    /* Get interface stats for each domain. */
    for (i = 0; i < nr_interface_devices; ++i) {
        struct _virDomainInterfaceStats stats;

        if (virDomainInterfaceStats (interface_devices[i].dom,
                    interface_devices[i].path,
                    &stats, sizeof stats) != 0)
            continue;

	if ((stats.rx_bytes != -1) && (stats.tx_bytes != -1))
	    submit_counter2 ("if_octets",
		    (counter_t) stats.rx_bytes, (counter_t) stats.tx_bytes,
		    t, interface_devices[i].dom, interface_devices[i].path);

	if ((stats.rx_packets != -1) && (stats.tx_packets != -1))
	    submit_counter2 ("if_packets",
		    (counter_t) stats.rx_packets, (counter_t) stats.tx_packets,
		    t, interface_devices[i].dom, interface_devices[i].path);

	if ((stats.rx_errs != -1) && (stats.tx_errs != -1))
	    submit_counter2 ("if_errors",
		    (counter_t) stats.rx_errs, (counter_t) stats.tx_errs,
		    t, interface_devices[i].dom, interface_devices[i].path);

	if ((stats.rx_drop != -1) && (stats.tx_drop != -1))
	    submit_counter2 ("if_dropped",
		    (counter_t) stats.rx_drop, (counter_t) stats.tx_drop,
		    t, interface_devices[i].dom, interface_devices[i].path);
    } /* for (nr_interface_devices) */

    return 0;
}