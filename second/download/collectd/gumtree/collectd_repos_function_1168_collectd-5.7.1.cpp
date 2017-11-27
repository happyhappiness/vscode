static int cna_handle_volume_usage_data(const host_config_t *host, /* {{{ */
                                        cfg_volume_usage_t *cfg_volume,
                                        na_elem_t *data) {
  na_elem_t *elem_volumes;
  na_elem_iter_t iter_volume;

  elem_volumes = na_elem_child(data, "volumes");
  if (elem_volumes == NULL) {
    ERROR("netapp plugin: cna_handle_volume_usage_data: "
          "na_elem_child (\"volumes\") failed "
          "for host %s.",
          host->name);
    return (-1);
  }

  iter_volume = na_child_iterator(elem_volumes);
  for (na_elem_t *elem_volume = na_iterator_next(&iter_volume);
       elem_volume != NULL; elem_volume = na_iterator_next(&iter_volume)) {
    const char *volume_name, *state;

    data_volume_usage_t *v;
    uint64_t value;

    na_elem_t *sis;

    volume_name = na_child_get_string(elem_volume, "name");
    if (volume_name == NULL)
      continue;

    state = na_child_get_string(elem_volume, "state");
    if ((state == NULL) || (strcmp(state, "online") != 0))
      continue;

    /* get_volume_usage may return NULL if the volume is to be ignored. */
    v = get_volume_usage(cfg_volume, volume_name);
    if (v == NULL)
      continue;

    if ((v->flags & CFG_VOLUME_USAGE_SNAP) != 0)
      cna_handle_volume_snap_usage(host, v);

    if ((v->flags & CFG_VOLUME_USAGE_DF) == 0)
      continue;

    /* 2^4 exa-bytes? This will take a while ;) */
    value = na_child_get_uint64(elem_volume, "size-available", UINT64_MAX);
    if (value != UINT64_MAX) {
      v->norm_free = value;
      v->flags |= HAVE_VOLUME_USAGE_NORM_FREE;
    }

    value = na_child_get_uint64(elem_volume, "size-used", UINT64_MAX);
    if (value != UINT64_MAX) {
      v->norm_used = value;
      v->flags |= HAVE_VOLUME_USAGE_NORM_USED;
    }

    value = na_child_get_uint64(elem_volume, "snapshot-blocks-reserved",
                                UINT64_MAX);
    if (value != UINT64_MAX) {
      /* 1 block == 1024 bytes  as per API docs */
      v->snap_reserved = 1024 * value;
      v->flags |= HAVE_VOLUME_USAGE_SNAP_RSVD;
    }

    sis = na_elem_child(elem_volume, "sis");
    if (sis != NULL) {
      cna_handle_volume_sis_data(host, v, sis);
      cna_handle_volume_sis_saved(host, v, sis);
    }
  } /* for (elem_volume) */

  return (cna_submit_volume_usage_data(
      host->name, cfg_volume, host->cfg_volume_usage->interval.interval));
}