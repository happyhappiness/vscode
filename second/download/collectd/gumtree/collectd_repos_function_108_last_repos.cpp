static int refresh_lists(struct lv_read_instance *inst) {
  struct lv_read_state *state = &inst->read_state;
  int n;

  n = virConnectNumOfDomains(conn);
  if (n < 0) {
    VIRT_ERROR(conn, "reading number of domains");
    return -1;
  }

  lv_clean_read_state(state);

  if (n > 0) {
#ifdef HAVE_LIST_ALL_DOMAINS
    virDomainPtr *domains;
    n = virConnectListAllDomains(conn, &domains,
                                 VIR_CONNECT_LIST_DOMAINS_ACTIVE);
#else
    int *domids;

    /* Get list of domains. */
    domids = malloc(sizeof(*domids) * n);
    if (domids == NULL) {
      ERROR(PLUGIN_NAME " plugin: malloc failed.");
      return -1;
    }

    n = virConnectListDomains(conn, domids, n);
#endif

    if (n < 0) {
      VIRT_ERROR(conn, "reading list of domains");
#ifndef HAVE_LIST_ALL_DOMAINS
      sfree(domids);
#endif
      return -1;
    }

    /* Fetch each domain and add it to the list, unless ignore. */
    for (int i = 0; i < n; ++i) {
      const char *name;
      char *xml = NULL;
      xmlDocPtr xml_doc = NULL;
      xmlXPathContextPtr xpath_ctx = NULL;
      xmlXPathObjectPtr xpath_obj = NULL;
      char tag[PARTITION_TAG_MAX_LEN] = {'\0'};
      virDomainInfo info;
      int status;

#ifdef HAVE_LIST_ALL_DOMAINS
      virDomainPtr dom = domains[i];
#else
      virDomainPtr dom = NULL;
      dom = virDomainLookupByID(conn, domids[i]);
      if (dom == NULL) {
        VIRT_ERROR(conn, "virDomainLookupByID");
        /* Could be that the domain went away -- ignore it anyway. */
        continue;
      }
#endif

      name = virDomainGetName(dom);
      if (name == NULL) {
        VIRT_ERROR(conn, "virDomainGetName");
        goto cont;
      }

      status = virDomainGetInfo(dom, &info);
      if (status != 0) {
        ERROR(PLUGIN_NAME " plugin: virDomainGetInfo failed with status %i.",
              status);
        continue;
      }

      if (info.state != VIR_DOMAIN_RUNNING) {
        DEBUG(PLUGIN_NAME " plugin: skipping inactive domain %s", name);
        continue;
      }

      if (il_domains && ignorelist_match(il_domains, name) != 0)
        goto cont;

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

      if (lv_domain_get_tag(xpath_ctx, name, tag) < 0) {
        ERROR(PLUGIN_NAME " plugin: lv_domain_get_tag failed.");
        goto cont;
      }

      if (!lv_instance_include_domain(inst, name, tag))
        goto cont;

      if (add_domain(state, dom) < 0) {
        ERROR(PLUGIN_NAME " plugin: malloc failed.");
        goto cont;
      }

      /* Block devices. */
      const char *bd_xmlpath = "/domain/devices/disk/target[@dev]";
      if (blockdevice_format == source)
        bd_xmlpath = "/domain/devices/disk/source[@dev]";
      xpath_obj = xmlXPathEval((const xmlChar *)bd_xmlpath, xpath_ctx);

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

        add_block_device(state, dom, path);
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

        add_interface_device(state, dom, path, address, j + 1);
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

#ifdef HAVE_LIST_ALL_DOMAINS
    sfree(domains);
#else
    sfree(domids);
#endif
  }

  DEBUG(PLUGIN_NAME " plugin#%s: refreshing"
                    " domains=%i block_devices=%i iface_devices=%i",
        inst->tag, state->nr_domains, state->nr_block_devices,
        state->nr_interface_devices);

  return 0;
}