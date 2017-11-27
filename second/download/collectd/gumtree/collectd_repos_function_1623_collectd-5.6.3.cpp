static int cx_handle_parsed_xml(xmlDocPtr doc, /* {{{ */
                                xmlXPathContextPtr xpath_ctx, cx_t *db) {
  llentry_t *le;
  const data_set_t *ds;
  cx_xpath_t *xpath;
  int status = -1;

  le = llist_head(db->list);
  while (le != NULL) {
    /* get the ds */
    xpath = (cx_xpath_t *)le->value;
    ds = plugin_get_ds(xpath->type);

    if ((cx_check_type(ds, xpath) == 0) &&
        (cx_handle_base_xpath(db->instance, cx_host(db), xpath_ctx, ds, le->key,
                              xpath) == 0))
      status = 0; /* we got atleast one success */

    le = le->next;
  } /* while (le != NULL) */

  return status;
}