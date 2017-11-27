static int ovs_db_json_data_process(ovs_db_t *pdb, const char *data,
                                    size_t len) {
  const char *method = NULL;
  char yajl_errbuf[OVS_YAJL_ERROR_BUFFER_SIZE];
  const char *method_path[] = {"method", NULL};
  const char *result_path[] = {"result", NULL};
  char *sjson = NULL;
  yajl_val jnode, jval;

  /* duplicate the data to make null-terminated string
   * required for yajl_tree_parse() */
  if ((sjson = calloc(1, len + 1)) == NULL)
    return -1;

  sstrncpy(sjson, data, len + 1);
  OVS_DEBUG("[len=%zu] %s", len, sjson);

  /* parse json data */
  jnode = yajl_tree_parse(sjson, yajl_errbuf, sizeof(yajl_errbuf));
  if (jnode == NULL) {
    OVS_ERROR("yajl_tree_parse() %s", yajl_errbuf);
    sfree(sjson);
    return -1;
  }

  /* get method name */
  if ((jval = yajl_tree_get(jnode, method_path, yajl_t_string)) != NULL) {
    if ((method = YAJL_GET_STRING(jval)) == NULL) {
      yajl_tree_free(jnode);
      sfree(sjson);
      return -1;
    }
    if (strcmp("echo", method) == 0) {
      /* echo request from the server */
      if (ovs_db_table_echo_cb(pdb, jnode) < 0)
        OVS_ERROR("handle echo request failed");
    } else if (strcmp("update", method) == 0) {
      /* update notification */
      if (ovs_db_table_update_cb(pdb, jnode) < 0)
        OVS_ERROR("handle update notification failed");
    }
  } else if ((jval = yajl_tree_get(jnode, result_path, yajl_t_any)) != NULL) {
    /* result notification */
    if (ovs_db_result_cb(pdb, jnode) < 0)
      OVS_ERROR("handle result reply failed");
  } else
    OVS_ERROR("connot find method or result failed");

  /* release memory */
  yajl_tree_free(jnode);
  sfree(sjson);
  return 0;
}