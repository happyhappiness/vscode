static int ovs_db_table_update_cb(ovs_db_t *pdb, yajl_val jnode) {
  ovs_callback_t *cb = NULL;
  yajl_val jvalue;
  yajl_val jparams;
  yajl_val jtable_updates;
  const char *params_path[] = {"params", NULL};
  const char *id_path[] = {"id", NULL};

  /* check & get request attributes */
  if ((jparams = yajl_tree_get(jnode, params_path, yajl_t_array)) == NULL ||
      (yajl_tree_get(jnode, id_path, yajl_t_null) == NULL)) {
    OVS_ERROR("invalid OVS DB request received");
    return -1;
  }

  /* check array length: [<json-value>, <table-updates>] */
  if ((YAJL_GET_ARRAY(jparams) == NULL) ||
      (YAJL_GET_ARRAY(jparams)->len != 2)) {
    OVS_ERROR("invalid OVS DB request received");
    return -1;
  }

  jvalue = YAJL_GET_ARRAY(jparams)->values[0];
  jtable_updates = YAJL_GET_ARRAY(jparams)->values[1];
  if ((!YAJL_IS_OBJECT(jtable_updates)) || (!YAJL_IS_STRING(jvalue))) {
    OVS_ERROR("invalid OVS DB request id or table update received");
    return -1;
  }

  /* find registered callback based on <json-value> */
  pthread_mutex_lock(&pdb->mutex);
  cb = ovs_db_table_callback_get(pdb, jvalue);
  if (cb == NULL || cb->table.call == NULL) {
    OVS_ERROR("No OVS DB table update callback found");
    pthread_mutex_unlock(&pdb->mutex);
    return -1;
  }

  /* call registered callback */
  cb->table.call(jtable_updates);
  pthread_mutex_unlock(&pdb->mutex);
  return 0;
}