static void ovs_events_table_update_cb(yajl_val jupdates) {
  yajl_val jnew_val = NULL;
  yajl_val jupdate = NULL;
  yajl_val jrow_update = NULL;
  ovs_events_iface_info_t ifinfo;

  /* JSON "Interface" table update example:
   * ---------------------------------
   * {"Interface":
   *  {
   *   "9adf1db2-29ca-4140-ab22-ae347a4484de":
   *    {
   *     "new":
   *      {
   *       "name":"br0",
   *       "link_state":"up"
   *      },
   *     "old":
   *      {
   *       "link_state":"down"
   *      }
   *    }
   *  }
   * }
   */
  if (!YAJL_IS_OBJECT(jupdates) || !(YAJL_GET_OBJECT(jupdates)->len > 0)) {
    ERROR(OVS_EVENTS_PLUGIN ": unexpected OVS DB update event received");
    return;
  }
  /* verify if this is a table event */
  jupdate = YAJL_GET_OBJECT(jupdates)->values[0];
  if (!YAJL_IS_OBJECT(jupdate)) {
    ERROR(OVS_EVENTS_PLUGIN ": unexpected table update event received");
    return;
  }
  /* go through all row updates  */
  for (size_t row_index = 0; row_index < YAJL_GET_OBJECT(jupdate)->len;
       ++row_index) {
    jrow_update = YAJL_GET_OBJECT(jupdate)->values[row_index];

    /* check row update */
    jnew_val = ovs_utils_get_value_by_key(jrow_update, "new");
    if (jnew_val == NULL) {
      ERROR(OVS_EVENTS_PLUGIN ": unexpected row update received");
      return;
    }
    /* get OVS DB interface information */
    if (ovs_events_get_iface_info(jnew_val, &ifinfo) < 0) {
      ERROR(OVS_EVENTS_PLUGIN
            " :unexpected interface information data received");
      return;
    }
    if (ovs_events_config_iface_exists(ifinfo.name) != 0) {
      DEBUG("name=%s, uuid=%s, ext_iface_id=%s, ext_vm_uuid=%s", ifinfo.name,
            ifinfo.uuid, ifinfo.ext_iface_id, ifinfo.ext_vm_uuid);
      /* dispatch notification */
      ovs_events_dispatch_notification(&ifinfo);
    }
  }
}