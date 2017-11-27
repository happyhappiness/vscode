static int cx_handle_parsed_xml(cx_t *db, xmlDocPtr doc, /* {{{ */
                                xmlXPathContextPtr xpath_ctx) {
  int status = -1;

  llentry_t *le = llist_head(db->xpath_list);
  while (le != NULL) {
    cx_xpath_t *xpath = (cx_xpath_t *)le->value;

    if (cx_handle_xpath(db, xpath_ctx, xpath) == 0)
      status = 0; /* we got atleast one success */

    le = le->next;
  } /* while (le != NULL) */

  return status;
}