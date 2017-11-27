static void ovs_events_poll_result_cb(yajl_val jresult, yajl_val jerror) {
  yajl_val *jvalues = NULL;
  yajl_val jvalue = NULL;
  ovs_events_iface_info_t ifinfo;

  if (!YAJL_IS_NULL(jerror)) {
    ERROR(OVS_EVENTS_PLUGIN "error received by OVS DB server");
    return;
  }

  /* result should be an array */
  if (!YAJL_IS_ARRAY(jresult)) {
    ERROR(OVS_EVENTS_PLUGIN "invalid data (array is expected)");
    return;
  }

  /* go through all rows and get interface info */
  jvalues = YAJL_GET_ARRAY(jresult)->values;
  for (size_t i = 0; i < YAJL_GET_ARRAY(jresult)->len; i++) {
    jvalue = ovs_utils_get_value_by_key(jvalues[i], "rows");
    if (jvalue == NULL || !YAJL_IS_ARRAY(jvalue)) {
      ERROR(OVS_EVENTS_PLUGIN "invalid data (array of rows is expected)");
      return;
    }
    /* get interfaces info */
    for (size_t j = 0; j < YAJL_GET_ARRAY(jvalue)->len; j++) {
      if (ovs_events_get_iface_info(YAJL_GET_ARRAY(jvalue)->values[j],
                                    &ifinfo) < 0) {
        ERROR(OVS_EVENTS_PLUGIN
              "unexpected interface information data received");
        return;
      }
      DEBUG("name=%s, uuid=%s, ext_iface_id=%s, ext_vm_uuid=%s", ifinfo.name,
            ifinfo.uuid, ifinfo.ext_iface_id, ifinfo.ext_vm_uuid);
      ovs_events_link_status_submit(&ifinfo);
    }
  }
}