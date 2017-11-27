static threshold_t *threshold_search (const data_set_t *ds,
    const value_list_t *vl)
{
  threshold_t *th;

  if ((th = threshold_get (vl->host, vl->plugin, vl->plugin_instance,
	  ds->type, vl->type_instance)) != NULL)
    return (th);
  else if ((th = threshold_get (vl->host, vl->plugin, vl->plugin_instance,
	  ds->type, NULL)) != NULL)
    return (th);
  else if ((th = threshold_get (vl->host, vl->plugin, NULL,
	  ds->type, vl->type_instance)) != NULL)
    return (th);
  else if ((th = threshold_get (vl->host, vl->plugin, NULL,
	  ds->type, NULL)) != NULL)
    return (th);
  else if ((th = threshold_get (vl->host, "", NULL,
	  ds->type, vl->type_instance)) != NULL)
    return (th);
  else if ((th = threshold_get (vl->host, "", NULL,
	  ds->type, NULL)) != NULL)
    return (th);
  else if ((th = threshold_get ("", vl->plugin, vl->plugin_instance,
	  ds->type, vl->type_instance)) != NULL)
    return (th);
  else if ((th = threshold_get ("", vl->plugin, vl->plugin_instance,
	  ds->type, NULL)) != NULL)
    return (th);
  else if ((th = threshold_get ("", vl->plugin, NULL,
	  ds->type, vl->type_instance)) != NULL)
    return (th);
  else if ((th = threshold_get ("", vl->plugin, NULL,
	  ds->type, NULL)) != NULL)
    return (th);
  else if ((th = threshold_get ("", "", NULL,
	  ds->type, vl->type_instance)) != NULL)
    return (th);
  else if ((th = threshold_get ("", "", NULL,
	  ds->type, NULL)) != NULL)
    return (th);

  return (NULL);
}