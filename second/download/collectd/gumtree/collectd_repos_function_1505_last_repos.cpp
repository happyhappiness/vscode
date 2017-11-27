static int c_ipmi_config_add_instance(oconfig_item_t *ci) {
  int status = 0;
  c_ipmi_instance_t *st = c_ipmi_init_instance();
  if (st == NULL)
    return ENOMEM;

  if (strcasecmp(ci->key, "Instance") == 0)
    status = cf_util_get_string(ci, &st->name);

  if (status != 0) {
    c_ipmi_free_instance(st);
    return status;
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Sensor", child->key) == 0)
      ignorelist_add(st->ignorelist, ci->values[0].value.string);
    else if (strcasecmp("IgnoreSelected", child->key) == 0) {
      _Bool t;
      status = cf_util_get_boolean(child, &t);
      if (status != 0)
        break;
      ignorelist_set_invert(st->ignorelist, /* invert = */ !t);
    } else if (strcasecmp("NotifyIPMIConnectionState", child->key) == 0) {
      status = cf_util_get_boolean(child, &st->notify_conn);
    } else if (strcasecmp("NotifySensorAdd", child->key) == 0) {
      status = cf_util_get_boolean(child, &st->notify_add);
    } else if (strcasecmp("NotifySensorRemove", child->key) == 0) {
      status = cf_util_get_boolean(child, &st->notify_remove);
    } else if (strcasecmp("NotifySensorNotPresent", child->key) == 0) {
      status = cf_util_get_boolean(child, &st->notify_notpresent);
    } else if (strcasecmp("SELEnabled", child->key) == 0) {
      status = cf_util_get_boolean(child, &st->sel_enabled);
    } else if (strcasecmp("SELClearEvent", child->key) == 0) {
      status = cf_util_get_boolean(child, &st->sel_clear_event);
    } else if (strcasecmp("Host", child->key) == 0)
      status = cf_util_get_string(child, &st->host);
    else if (strcasecmp("Address", child->key) == 0)
      status = cf_util_get_string(child, &st->connaddr);
    else if (strcasecmp("Username", child->key) == 0)
      status = cf_util_get_string(child, &st->username);
    else if (strcasecmp("Password", child->key) == 0)
      status = cf_util_get_string(child, &st->password);
    else if (strcasecmp("AuthType", child->key) == 0) {
      char tmp[8];
      status = cf_util_get_string_buffer(child, tmp, sizeof(tmp));
      if (status != 0)
        break;

      if (strcasecmp("MD5", tmp) == 0)
        st->authtype = IPMI_AUTHTYPE_MD5;
      else if (strcasecmp("rmcp+", tmp) == 0)
        st->authtype = IPMI_AUTHTYPE_RMCP_PLUS;
      else
        WARNING("ipmi plugin: The value \"%s\" is not valid for the "
                "\"AuthType\" option.",
                tmp);
    } else {
      WARNING("ipmi plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  if (status != 0) {
    c_ipmi_free_instance(st);
    return status;
  }

  c_ipmi_add_instance(st);

  return 0;
}