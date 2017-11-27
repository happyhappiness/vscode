static lcc_value_list_t *create_value_list (void) /* {{{ */
{
  lcc_value_list_t *vl;
  int host_num;

  vl = malloc (sizeof (*vl));
  if (vl == NULL)
  {
    fprintf (stderr, "malloc failed.\n");
    return (NULL);
  }
  memset (vl, 0, sizeof (*vl));

  vl->values = calloc (/* nmemb = */ 1, sizeof (*vl->values));
  if (vl->values == NULL)
  {
    fprintf (stderr, "calloc failed.\n");
    free (vl);
    return (NULL);
  }

  vl->values_types = calloc (/* nmemb = */ 1, sizeof (*vl->values_types));
  if (vl->values_types == NULL)
  {
    fprintf (stderr, "calloc failed.\n");
    free (vl->values);
    free (vl);
    return (NULL);
  }

  vl->values_len = 1;

  host_num = get_boundet_random (0, conf_num_hosts);

  vl->interval = conf_interval;
  vl->time = 1.0 + time (NULL)
    + (host_num % (1 + (int) vl->interval));

  if (get_boundet_random (0, 2) == 0)
    vl->values_types[0] = LCC_TYPE_GAUGE;
  else
    vl->values_types[0] = LCC_TYPE_DERIVE;

  snprintf (vl->identifier.host, sizeof (vl->identifier.host),
      "host%04i", host_num);
  snprintf (vl->identifier.plugin, sizeof (vl->identifier.plugin),
      "plugin%03i", get_boundet_random (0, conf_num_plugins));
  strncpy (vl->identifier.type,
      (vl->values_types[0] == LCC_TYPE_GAUGE) ? "gauge" : "derive",
      sizeof (vl->identifier.type));
  vl->identifier.type[sizeof (vl->identifier.type) - 1] = 0;
  snprintf (vl->identifier.type_instance, sizeof (vl->identifier.type_instance),
      "ti%li", random ());

  return (vl);
}