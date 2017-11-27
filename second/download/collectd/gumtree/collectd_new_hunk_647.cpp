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

static int refresh_lists(void) {
  int n;

  n = virConnectNumOfDomains(conn);
  if (n < 0) {
    VIRT_ERROR(conn, "reading number of domains");
    return -1;
  }

  if (n > 0) {
    int *domids;

    /* Get list of domains. */
    domids = malloc(sizeof(*domids) * n);
    if (domids == NULL) {
      ERROR(PLUGIN_NAME " plugin: malloc failed.");
      return -1;
    }

    n = virConnectListDomains(conn, domids, n);
    if (n < 0) {
      VIRT_ERROR(conn, "reading list of domains");
      sfree(domids);
      return -1;
    }

    free_block_devices();
    free_interface_devices();
    free_domains();

    /* Fetch each domain and add it to the list, unless ignore. */
    for (int i = 0; i < n; ++i) {
      virDomainPtr dom = NULL;
      const char *name;
      char *xml = NULL;
      xmlDocPtr xml_doc = NULL;
      xmlXPathContextPtr xpath_ctx = NULL;
      xmlXPathObjectPtr xpath_obj = NULL;

      dom = virDomainLookupByID(conn, domids[i]);
      if (dom == NULL) {
        VIRT_ERROR(conn, "virDomainLookupByID");
        /* Could be that the domain went away -- ignore it anyway. */
        continue;
      }

      name = virDomainGetName(dom);
      if (name == NULL) {
        VIRT_ERROR(conn, "virDomainGetName");
        goto cont;
      }

      if (il_domains && ignorelist_match(il_domains, name) != 0)
        goto cont;

      if (add_domain(dom) < 0) {
        ERROR(PLUGIN_NAME " plugin: malloc failed.");
        goto cont;
      }

      /* Get a list of devices for this domain. */
      xml = virDomainGetXMLDesc(dom, 0);
      if (!xml) {
        VIRT_ERROR(conn, "virDomainGetXMLDesc");
        goto cont;
      }

      /* Yuck, XML.  Parse out the devices. */
      xml_doc = xmlReadDoc((xmlChar *)xml, NULL, NULL, XML_PARSE_NONET);
      if (xml_doc == NULL) {
        VIRT_ERROR(conn, "xmlReadDoc");
        goto cont;
      }

      xpath_ctx = xmlXPathNewContext(xml_doc);

      /* Block devices. */
      xpath_obj = xmlXPathEval((xmlChar *)"/domain/devices/disk/target[@dev]",
                               xpath_ctx);
      if (xpath_obj == NULL || xpath_obj->type != XPATH_NODESET ||
          xpath_obj->nodesetval == NULL)
        goto cont;

      for (int j = 0; j < xpath_obj->nodesetval->nodeNr; ++j) {
        xmlNodePtr node;
        char *path = NULL;

        node = xpath_obj->nodesetval->nodeTab[j];
        if (!node)
          continue;
        path = (char *)xmlGetProp(node, (xmlChar *)"dev");
        if (!path)
          continue;

        if (il_block_devices &&
            ignore_device_match(il_block_devices, name, path) != 0)
          goto cont2;

        add_block_device(dom, path);
      cont2:
        if (path)
          xmlFree(path);
      }
      xmlXPathFreeObject(xpath_obj);

      /* Network interfaces. */
      xpath_obj = xmlXPathEval(
          (xmlChar *)"/domain/devices/interface[target[@dev]]", xpath_ctx);
      if (xpath_obj == NULL || xpath_obj->type != XPATH_NODESET ||
          xpath_obj->nodesetval == NULL)
        goto cont;

      xmlNodeSetPtr xml_interfaces = xpath_obj->nodesetval;

      for (int j = 0; j < xml_interfaces->nodeNr; ++j) {
        char *path = NULL;
        char *address = NULL;
        xmlNodePtr xml_interface;

        xml_interface = xml_interfaces->nodeTab[j];
        if (!xml_interface)
          continue;

        for (xmlNodePtr child = xml_interface->children; child;
             child = child->next) {
          if (child->type != XML_ELEMENT_NODE)
            continue;

          if (xmlStrEqual(child->name, (const xmlChar *)"target")) {
            path = (char *)xmlGetProp(child, (const xmlChar *)"dev");
            if (!path)
              continue;
          } else if (xmlStrEqual(child->name, (const xmlChar *)"mac")) {
            address = (char *)xmlGetProp(child, (const xmlChar *)"address");
            if (!address)
              continue;
          }
        }

        if (il_interface_devices &&
            (ignore_device_match(il_interface_devices, name, path) != 0 ||
             ignore_device_match(il_interface_devices, name, address) != 0))
          goto cont3;

        add_interface_device(dom, path, address, j + 1);
      cont3:
        if (path)
          xmlFree(path);
        if (address)
          xmlFree(address);
      }

    cont:
      if (xpath_obj)
        xmlXPathFreeObject(xpath_obj);
      if (xpath_ctx)
        xmlXPathFreeContext(xpath_ctx);
      if (xml_doc)
        xmlFreeDoc(xml_doc);
      sfree(xml);
    }

    sfree(domids);
  }

  return 0;
}

static void free_domains(void) {
  if (domains) {
    for (int i = 0; i < nr_domains; ++i)
      virDomainFree(domains[i]);
    sfree(domains);
  }
  domains = NULL;
  nr_domains = 0;
}

static int add_domain(virDomainPtr dom) {
  virDomainPtr *new_ptr;
  int new_size = sizeof(domains[0]) * (nr_domains + 1);

  if (domains)
    new_ptr = realloc(domains, new_size);
  else
    new_ptr = malloc(new_size);

  if (new_ptr == NULL)
    return -1;

  domains = new_ptr;
  domains[nr_domains] = dom;
  return nr_domains++;
}

static void free_block_devices(void) {
  if (block_devices) {
    for (int i = 0; i < nr_block_devices; ++i)
      sfree(block_devices[i].path);
    sfree(block_devices);
  }
  block_devices = NULL;
  nr_block_devices = 0;
}

static int add_block_device(virDomainPtr dom, const char *path) {
  struct block_device *new_ptr;
  int new_size = sizeof(block_devices[0]) * (nr_block_devices + 1);
  char *path_copy;

  path_copy = strdup(path);
  if (!path_copy)
    return -1;

  if (block_devices)
    new_ptr = realloc(block_devices, new_size);
  else
    new_ptr = malloc(new_size);

  if (new_ptr == NULL) {
    sfree(path_copy);
    return -1;
  }
  block_devices = new_ptr;
  block_devices[nr_block_devices].dom = dom;
  block_devices[nr_block_devices].path = path_copy;
  return nr_block_devices++;
}

static void free_interface_devices(void) {
  if (interface_devices) {
    for (int i = 0; i < nr_interface_devices; ++i) {
      sfree(interface_devices[i].path);
      sfree(interface_devices[i].address);
      sfree(interface_devices[i].number);
    }
    sfree(interface_devices);
  }
  interface_devices = NULL;
  nr_interface_devices = 0;
}

static int add_interface_device(virDomainPtr dom, const char *path,
                                const char *address, unsigned int number) {
  struct interface_device *new_ptr;
  int new_size = sizeof(interface_devices[0]) * (nr_interface_devices + 1);
  char *path_copy, *address_copy, number_string[15];

  if ((path == NULL) || (address == NULL))
    return EINVAL;

  path_copy = strdup(path);
  if (!path_copy)
    return -1;

  address_copy = strdup(address);
  if (!address_copy) {
    sfree(path_copy);
    return -1;
  }

  snprintf(number_string, sizeof(number_string), "interface-%u", number);

  if (interface_devices)
    new_ptr = realloc(interface_devices, new_size);
  else
    new_ptr = malloc(new_size);

  if (new_ptr == NULL) {
    sfree(path_copy);
    sfree(address_copy);
    return -1;
  }
  interface_devices = new_ptr;
  interface_devices[nr_interface_devices].dom = dom;
  interface_devices[nr_interface_devices].path = path_copy;
  interface_devices[nr_interface_devices].address = address_copy;
  interface_devices[nr_interface_devices].number = strdup(number_string);
  return nr_interface_devices++;
}

static int ignore_device_match(ignorelist_t *il, const char *domname,
                               const char *devpath) {
  char *name;
  int n, r;

  if ((domname == NULL) || (devpath == NULL))
    return 0;

  n = sizeof(char) * (strlen(domname) + strlen(devpath) + 2);
  name = malloc(n);
  if (name == NULL) {
    ERROR(PLUGIN_NAME " plugin: malloc failed.");
    return 0;
  }
  ssnprintf(name, n, "%s:%s", domname, devpath);
  r = ignorelist_match(il, name);
  sfree(name);
  return r;
}

static int lv_shutdown(void) {
  free_block_devices();
  free_interface_devices();
  free_domains();

  if (conn != NULL)
    virConnectClose(conn);
  conn = NULL;

  ignorelist_free(il_domains);
  il_domains = NULL;
  ignorelist_free(il_block_devices);
  il_block_devices = NULL;
  ignorelist_free(il_interface_devices);
  il_interface_devices = NULL;

  return 0;
}

void module_register(void) {
  plugin_register_config(PLUGIN_NAME, lv_config, config_keys, NR_CONFIG_KEYS);
  plugin_register_init(PLUGIN_NAME, lv_init);
  plugin_register_read(PLUGIN_NAME, lv_read);
  plugin_register_shutdown(PLUGIN_NAME, lv_shutdown);
}

/*
 * vim: shiftwidth=4 tabstop=8 softtabstop=4 expandtab fdm=marker
 */
