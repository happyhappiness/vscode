threshold_t *threshold_search(const value_list_t *vl) { /* {{{ */
  threshold_t *th;

  if ((th = threshold_get(vl->host, vl->plugin, vl->plugin_instance, vl->type,
                          vl->type_instance)) != NULL)
    return th;
  else if ((th = threshold_get(vl->host, vl->plugin, vl->plugin_instance,
                               vl->type, NULL)) != NULL)
    return th;
  else if ((th = threshold_get(vl->host, vl->plugin, NULL, vl->type,
                               vl->type_instance)) != NULL)
    return th;
  else if ((th = threshold_get(vl->host, vl->plugin, NULL, vl->type, NULL)) !=
           NULL)
    return th;
  else if ((th = threshold_get(vl->host, "", NULL, vl->type,
                               vl->type_instance)) != NULL)
    return th;
  else if ((th = threshold_get(vl->host, "", NULL, vl->type, NULL)) != NULL)
    return th;
  else if ((th = threshold_get("", vl->plugin, vl->plugin_instance, vl->type,
                               vl->type_instance)) != NULL)
    return th;
  else if ((th = threshold_get("", vl->plugin, vl->plugin_instance, vl->type,
                               NULL)) != NULL)
    return th;
  else if ((th = threshold_get("", vl->plugin, NULL, vl->type,
                               vl->type_instance)) != NULL)
    return th;
  else if ((th = threshold_get("", vl->plugin, NULL, vl->type, NULL)) != NULL)
    return th;
  else if ((th = threshold_get("", "", NULL, vl->type, vl->type_instance)) !=
           NULL)
    return th;
  else if ((th = threshold_get("", "", NULL, vl->type, NULL)) != NULL)
    return th;

  return NULL;
}