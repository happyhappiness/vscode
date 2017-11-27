static void free_cfg_volume_usage(cfg_volume_usage_t *cvu) /* {{{ */
{
  data_volume_usage_t *data;

  if (cvu == NULL)
    return;

  /* Free the ignorelists */
  ignorelist_free(cvu->il_capacity);
  ignorelist_free(cvu->il_snapshot);

  /* Free the linked list of volumes */
  data = cvu->volumes;
  while (data != NULL) {
    data_volume_usage_t *next = data->next;
    sfree(data->name);
    if (data->snap_query != NULL)
      na_elem_free(data->snap_query);
    sfree(data);
    data = next;
  }

  if (cvu->query != NULL)
    na_elem_free(cvu->query);

  sfree(cvu);
}