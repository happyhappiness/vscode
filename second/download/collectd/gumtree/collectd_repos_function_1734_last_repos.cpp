static int ovs_db_table_echo_cb(const ovs_db_t *pdb, yajl_val jnode) {
  yajl_val jparams;
  yajl_val jid;
  yajl_gen jgen;
  size_t resp_len = 0;
  const char *resp = NULL;
  const char *params_path[] = {"params", NULL};
  const char *id_path[] = {"id", NULL};
  yajl_gen_status yajl_gen_ret;

  if ((jgen = yajl_gen_alloc(NULL)) == NULL)
    return -1;

  /* check & get request attributes */
  if ((jparams = yajl_tree_get(jnode, params_path, yajl_t_array)) == NULL ||
      ((jid = yajl_tree_get(jnode, id_path, yajl_t_any)) == NULL)) {
    OVS_ERROR("parse echo request failed");
    goto yajl_gen_failure;
  }

  /* generate JSON echo response */
  OVS_YAJL_CALL(yajl_gen_map_open, jgen);

  OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, "result");
  OVS_YAJL_CALL(ovs_yajl_gen_val, jgen, jparams);

  OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, "error");
  OVS_YAJL_CALL(yajl_gen_null, jgen);

  OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, "id");
  OVS_YAJL_CALL(ovs_yajl_gen_val, jgen, jid);

  OVS_YAJL_CALL(yajl_gen_map_close, jgen);
  OVS_YAJL_CALL(yajl_gen_get_buf, jgen, (const unsigned char **)&resp,
                &resp_len);

  /* send the response */
  OVS_DEBUG("response: %s", resp);
  if (ovs_db_data_send(pdb, resp, resp_len) < 0) {
    OVS_ERROR("send echo reply failed");
    goto yajl_gen_failure;
  }
  /* clean up and return success */
  yajl_gen_clear(jgen);
  return 0;

yajl_gen_failure:
  /* release memory */
  yajl_gen_clear(jgen);
  return -1;
}