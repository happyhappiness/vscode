static int ovs_events_get_iface_info(yajl_val jobject,
                                     ovs_events_iface_info_t *ifinfo) {
  yajl_val jexternal_ids = NULL;
  yajl_val jvalue = NULL;
  yajl_val juuid = NULL;
  const char *state = NULL;

  /* check YAJL type */
  if (!YAJL_IS_OBJECT(jobject))
    return -1;

  /* zero the interface info structure */
  memset(ifinfo, 0, sizeof(*ifinfo));

  /* try to find external_ids, name and link_state fields */
  jexternal_ids = ovs_utils_get_value_by_key(jobject, "external_ids");
  if (jexternal_ids == NULL || ifinfo == NULL)
    return -1;

  /* get iface-id from external_ids field */
  jvalue = ovs_utils_get_map_value(jexternal_ids, "iface-id");
  if (jvalue != NULL && YAJL_IS_STRING(jvalue))
    sstrncpy(ifinfo->ext_iface_id, YAJL_GET_STRING(jvalue),
             sizeof(ifinfo->ext_iface_id));

  /* get vm-uuid from external_ids field */
  jvalue = ovs_utils_get_map_value(jexternal_ids, "vm-uuid");
  if (jvalue != NULL && YAJL_IS_STRING(jvalue))
    sstrncpy(ifinfo->ext_vm_uuid, YAJL_GET_STRING(jvalue),
             sizeof(ifinfo->ext_vm_uuid));

  /* get interface uuid */
  jvalue = ovs_utils_get_value_by_key(jobject, "_uuid");
  if (jvalue == NULL || !YAJL_IS_ARRAY(jvalue) ||
      YAJL_GET_ARRAY(jvalue)->len != 2)
    return -1;
  juuid = YAJL_GET_ARRAY(jvalue)->values[1];
  if (juuid == NULL || !YAJL_IS_STRING(juuid))
    return -1;
  sstrncpy(ifinfo->uuid, YAJL_GET_STRING(juuid), sizeof(ifinfo->uuid));

  /* get interface name */
  jvalue = ovs_utils_get_value_by_key(jobject, "name");
  if (jvalue == NULL || !YAJL_IS_STRING(jvalue))
    return -1;
  sstrncpy(ifinfo->name, YAJL_GET_STRING(jvalue), sizeof(ifinfo->name));

  /* get OVS DB interface link status */
  jvalue = ovs_utils_get_value_by_key(jobject, "link_state");
  if (jvalue != NULL && ((state = YAJL_GET_STRING(jvalue)) != NULL)) {
    /* convert OVS table link state to link status */
    if (strcmp(state, "up") == 0)
      ifinfo->link_status = UP;
    else if (strcmp(state, "down") == 0)
      ifinfo->link_status = DOWN;
  }
  return 0;
}