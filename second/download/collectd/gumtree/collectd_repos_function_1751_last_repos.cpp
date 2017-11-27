int ovs_db_table_cb_register(ovs_db_t *pdb, const char *tb_name,
                             const char **tb_column,
                             ovs_db_table_cb_t update_cb,
                             ovs_db_result_cb_t result_cb, unsigned int flags) {
  yajl_gen jgen;
  yajl_gen_status yajl_gen_ret;
  ovs_callback_t *new_cb = NULL;
  char uid_str[OVS_UID_STR_SIZE];
  char *params;
  size_t params_len;
  int ovs_db_ret = 0;

  /* sanity check */
  if (pdb == NULL || tb_name == NULL || update_cb == NULL)
    return -1;

  /* allocate new update callback */
  if ((new_cb = calloc(1, sizeof(ovs_callback_t))) == NULL)
    return -1;

  /* init YAJL generator */
  if ((jgen = yajl_gen_alloc(NULL)) == NULL) {
    sfree(new_cb);
    return -1;
  }

  /* add new callback to front */
  new_cb->table.call = update_cb;
  new_cb->uid = ovs_uid_generate();
  ovs_db_callback_add(pdb, new_cb);

  /* make update notification request
   * [<db-name>, <json-value>, <monitor-requests>] */
  OVS_YAJL_CALL(yajl_gen_array_open, jgen);
  {
    OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, OVS_DB_DEFAULT_DB_NAME);

    /* uid string <json-value> */
    snprintf(uid_str, sizeof(uid_str), "%" PRIX64, new_cb->uid);
    OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, uid_str);

    /* <monitor-requests> */
    OVS_YAJL_CALL(yajl_gen_map_open, jgen);
    {
      OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, tb_name);
      OVS_YAJL_CALL(yajl_gen_array_open, jgen);
      {
        /* <monitor-request> */
        OVS_YAJL_CALL(yajl_gen_map_open, jgen);
        {
          if (tb_column) {
            /* columns within the table to be monitored */
            OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, "columns");
            OVS_YAJL_CALL(yajl_gen_array_open, jgen);
            for (; *tb_column; tb_column++)
              OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, *tb_column);
            OVS_YAJL_CALL(yajl_gen_array_close, jgen);
          }
          /* specify select option */
          OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, "select");
          {
            OVS_YAJL_CALL(yajl_gen_map_open, jgen);
            {
              OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, "initial");
              OVS_YAJL_CALL(yajl_gen_bool, jgen,
                            flags & OVS_DB_TABLE_CB_FLAG_INITIAL);
              OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, "insert");
              OVS_YAJL_CALL(yajl_gen_bool, jgen,
                            flags & OVS_DB_TABLE_CB_FLAG_INSERT);
              OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, "delete");
              OVS_YAJL_CALL(yajl_gen_bool, jgen,
                            flags & OVS_DB_TABLE_CB_FLAG_DELETE);
              OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, "modify");
              OVS_YAJL_CALL(yajl_gen_bool, jgen,
                            flags & OVS_DB_TABLE_CB_FLAG_MODIFY);
            }
            OVS_YAJL_CALL(yajl_gen_map_close, jgen);
          }
        }
        OVS_YAJL_CALL(yajl_gen_map_close, jgen);
      }
      OVS_YAJL_CALL(yajl_gen_array_close, jgen);
    }
    OVS_YAJL_CALL(yajl_gen_map_close, jgen);
  }
  OVS_YAJL_CALL(yajl_gen_array_close, jgen);

  /* make a request to subscribe to given table */
  OVS_YAJL_CALL(yajl_gen_get_buf, jgen, (const unsigned char **)&params,
                &params_len);
  if (ovs_db_send_request(pdb, "monitor", params, result_cb) < 0) {
    OVS_ERROR("Failed to subscribe to \"%s\" table", tb_name);
    ovs_db_ret = (-1);
  }

yajl_gen_failure:
  /* release memory */
  yajl_gen_clear(jgen);
  return ovs_db_ret;
}