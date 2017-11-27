int plugin_dispatch_values_secure (const value_list_t *vl)
{
  value_list_t vl_copy;
  int status;

  if (vl == NULL)
    return EINVAL;

  memcpy (&vl_copy, vl, sizeof (vl_copy));

  /* Write callbacks must not change the values and meta pointers, so we can
   * savely skip copying those and make this more efficient. */
  if ((pre_cache_chain == NULL) && (post_cache_chain == NULL))
    return (plugin_dispatch_values (&vl_copy));

  /* Set pointers to NULL, just to be on the save side. */
  vl_copy.values = NULL;
  vl_copy.meta = NULL;

  vl_copy.values = malloc (sizeof (*vl_copy.values) * vl->values_len);
  if (vl_copy.values == NULL)
  {
    ERROR ("plugin_dispatch_values_secure: malloc failed.");
    return (ENOMEM);
  }
  memcpy (vl_copy.values, vl->values, sizeof (*vl_copy.values) * vl->values_len);

  if (vl->meta != NULL)
  {
    vl_copy.meta = meta_data_clone (vl->meta);
    if (vl_copy.meta == NULL)
    {
      ERROR ("plugin_dispatch_values_secure: meta_data_clone failed.");
      free (vl_copy.values);
      return (ENOMEM);
    }
  } /* if (vl->meta) */

  status = plugin_dispatch_values (&vl_copy);

  meta_data_destroy (vl_copy.meta);
  free (vl_copy.values);

  return (status);
}