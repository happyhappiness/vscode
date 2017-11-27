static int lv_read(void) {
  time_t t;

  if (conn == NULL) {
    /* `conn_string == NULL' is acceptable. */
    conn = virConnectOpenReadOnly(conn_string);
    if (conn == NULL) {
      c_complain(LOG_ERR, &conn_complain,
                 PLUGIN_NAME " plugin: Unable to connect: "
                             "virConnectOpenReadOnly failed.");
      return -1;
    }
  }
  c_release(LOG_NOTICE, &conn_complain,
            PLUGIN_NAME " plugin: Connection established.");

  time(&t);

  /* Need to refresh domain or device lists? */
  if ((last_refresh == (time_t)0) ||
      ((interval > 0) && ((last_refresh + interval) <= t))) {
    if (refresh_lists() != 0) {
      if (conn != NULL)
        virConnectClose(conn);
      conn = NULL;
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

    status = virDomainGetInfo(domains[i], &info);
    if (status != 0) {
      ERROR(PLUGIN_NAME " plugin: virDomainGetInfo failed with status %i.",
            status);
      continue;
    }

    if (info.state != VIR_DOMAIN_RUNNING) {
      /* only gather stats for running domains */
      continue;
    }

    cpu_submit(info.cpuTime, domains[i], "virt_cpu_total");
    memory_submit((gauge_t)info.memory * 1024, domains[i]);

    vinfo = malloc(info.nrVirtCpu * sizeof(vinfo[0]));
    if (vinfo == NULL) {
      ERROR(PLUGIN_NAME " plugin: malloc failed.");
      continue;
    }

    status = virDomainGetVcpus(domains[i], vinfo, info.nrVirtCpu,
                               /* cpu map = */ NULL, /* cpu map length = */ 0);
    if (status < 0) {
      ERROR(PLUGIN_NAME " plugin: virDomainGetVcpus failed with status %i.",
            status);
      sfree(vinfo);
      continue;
    }

    for (int j = 0; j < info.nrVirtCpu; ++j)
      vcpu_submit(vinfo[j].cpuTime, domains[i], vinfo[j].number, "virt_vcpu");

    sfree(vinfo);

    minfo =
        malloc(VIR_DOMAIN_MEMORY_STAT_NR * sizeof(virDomainMemoryStatStruct));
    if (minfo == NULL) {
      ERROR("virt plugin: malloc failed.");
      continue;
    }

    status =
        virDomainMemoryStats(domains[i], minfo, VIR_DOMAIN_MEMORY_STAT_NR, 0);

    if (status < 0) {
      ERROR("virt plugin: virDomainMemoryStats failed with status %i.", status);
      sfree(minfo);
      continue;
    }

    for (int j = 0; j < status; j++) {
      memory_stats_submit((gauge_t)minfo[j].val * 1024, domains[i],
                          minfo[j].tag);
    }

    sfree(minfo);
  }

  /* Get block device stats for each domain. */
  for (int i = 0; i < nr_block_devices; ++i) {
    struct _virDomainBlockStats stats;

    if (virDomainBlockStats(block_devices[i].dom, block_devices[i].path, &stats,
                            sizeof stats) != 0)
      continue;

    if ((stats.rd_req != -1) && (stats.wr_req != -1))
      submit_derive2("disk_ops", (derive_t)stats.rd_req, (derive_t)stats.wr_req,
                     block_devices[i].dom, block_devices[i].path);

    if ((stats.rd_bytes != -1) && (stats.wr_bytes != -1))
      submit_derive2("disk_octets", (derive_t)stats.rd_bytes,
                     (derive_t)stats.wr_bytes, block_devices[i].dom,
                     block_devices[i].path);
  } /* for (nr_block_devices) */

  /* Get interface stats for each domain. */
  for (int i = 0; i < nr_interface_devices; ++i) {
    struct _virDomainInterfaceStats stats;
    char *display_name = NULL;

    switch (interface_format) {
    case if_address:
      display_name = interface_devices[i].address;
      break;
    case if_number:
      display_name = interface_devices[i].number;
      break;
    case if_name:
    default:
      display_name = interface_devices[i].path;
    }

    if (virDomainInterfaceStats(interface_devices[i].dom,
                                interface_devices[i].path, &stats,
                                sizeof stats) != 0)
      continue;

    if ((stats.rx_bytes != -1) && (stats.tx_bytes != -1))
      submit_derive2("if_octets", (derive_t)stats.rx_bytes,
                     (derive_t)stats.tx_bytes, interface_devices[i].dom,
                     display_name);

    if ((stats.rx_packets != -1) && (stats.tx_packets != -1))
      submit_derive2("if_packets", (derive_t)stats.rx_packets,
                     (derive_t)stats.tx_packets, interface_devices[i].dom,
                     display_name);

    if ((stats.rx_errs != -1) && (stats.tx_errs != -1))
      submit_derive2("if_errors", (derive_t)stats.rx_errs,
                     (derive_t)stats.tx_errs, interface_devices[i].dom,
                     display_name);

    if ((stats.rx_drop != -1) && (stats.tx_drop != -1))
      submit_derive2("if_dropped", (derive_t)stats.rx_drop,
                     (derive_t)stats.tx_drop, interface_devices[i].dom,
                     display_name);
  } /* for (nr_interface_devices) */

  return 0;
}