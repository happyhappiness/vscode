static int cj_get_type (cj_key_t *key)
{
  const data_set_t *ds;

  ds = plugin_get_ds (key->type);
  if (ds == NULL)
    return -1; /* let plugin_write do the complaining */
  else
    return ds->ds[0].type; /* XXX support ds->ds_len > 1 */
}