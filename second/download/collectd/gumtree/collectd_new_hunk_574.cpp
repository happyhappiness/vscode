    fprintf (fh, "PluginInstance: %s\n", n->plugin_instance);
  if (strlen (n->type) > 0)
    fprintf (fh, "Type: %s\n", n->type);
  if (strlen (n->type_instance) > 0)
    fprintf (fh, "TypeInstance: %s\n", n->type_instance);

  for (notification_meta_t *meta = n->meta; meta != NULL; meta = meta->next)
  {
    if (meta->type == NM_TYPE_STRING)
      fprintf (fh, "%s: %s\n", meta->name, meta->nm_value.nm_string);
    else if (meta->type == NM_TYPE_SIGNED_INT)
      fprintf (fh, "%s: %"PRIi64"\n", meta->name, meta->nm_value.nm_signed_int);
    else if (meta->type == NM_TYPE_UNSIGNED_INT)
