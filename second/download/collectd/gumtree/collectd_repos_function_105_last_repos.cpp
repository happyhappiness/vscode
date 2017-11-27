static int lv_domain_get_tag(xmlXPathContextPtr xpath_ctx, const char *dom_name,
                             char *dom_tag) {
  char xpath_str[BUFFER_MAX_LEN] = {'\0'};
  xmlXPathObjectPtr xpath_obj = NULL;
  xmlNodePtr xml_node = NULL;
  int ret = -1;
  int err;

  err = xmlXPathRegisterNs(xpath_ctx,
                           (const xmlChar *)METADATA_VM_PARTITION_PREFIX,
                           (const xmlChar *)METADATA_VM_PARTITION_URI);
  if (err) {
    ERROR(PLUGIN_NAME " plugin: xmlXpathRegisterNs(%s, %s) failed on domain %s",
          METADATA_VM_PARTITION_PREFIX, METADATA_VM_PARTITION_URI, dom_name);
    goto done;
  }

  snprintf(xpath_str, sizeof(xpath_str), "/domain/metadata/%s:%s/text()",
           METADATA_VM_PARTITION_PREFIX, METADATA_VM_PARTITION_ELEMENT);
  xpath_obj = xmlXPathEvalExpression((xmlChar *)xpath_str, xpath_ctx);
  if (xpath_obj == NULL) {
    ERROR(PLUGIN_NAME " plugin: xmlXPathEval(%s) failed on domain %s",
          xpath_str, dom_name);
    goto done;
  }

  if (xpath_obj->type != XPATH_NODESET) {
    ERROR(PLUGIN_NAME " plugin: xmlXPathEval(%s) unexpected return type %d "
                      "(wanted %d) on domain %s",
          xpath_str, xpath_obj->type, XPATH_NODESET, dom_name);
    goto done;
  }

  /*
   * from now on there is no real error, it's ok if a domain
   * doesn't have the metadata partition tag.
   */
  ret = 0;
  if (xpath_obj->nodesetval == NULL || xpath_obj->nodesetval->nodeNr != 1) {
    DEBUG(PLUGIN_NAME " plugin: xmlXPathEval(%s) return nodeset size=%i "
                      "expected=1 on domain %s",
          xpath_str,
          (xpath_obj->nodesetval == NULL) ? 0 : xpath_obj->nodesetval->nodeNr,
          dom_name);
  } else {
    xml_node = xpath_obj->nodesetval->nodeTab[0];
    sstrncpy(dom_tag, (const char *)xml_node->content, PARTITION_TAG_MAX_LEN);
  }

done:
  /* deregister to clean up */
  err = xmlXPathRegisterNs(xpath_ctx,
                           (const xmlChar *)METADATA_VM_PARTITION_PREFIX, NULL);
  if (err) {
    /* we can't really recover here */
    ERROR(PLUGIN_NAME
          " plugin: deregistration of namespace %s failed for domain %s",
          METADATA_VM_PARTITION_PREFIX, dom_name);
  }
  if (xpath_obj)
    xmlXPathFreeObject(xpath_obj);

  return ret;
}