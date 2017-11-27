static int mc_handle_metadata_msg (Ganglia_metadata_msg *msg) /* {{{ */
{
  switch (msg->id)
  {
    case gmetadata_full:
    {
      Ganglia_metadatadef msg_meta;
      staging_entry_t *se;
      const data_set_t *ds;
      metric_map_t *map;

      msg_meta = msg->Ganglia_metadata_msg_u.gfull;

      if (msg_meta.metric.tmax <= 0)
        return (-1);

      map = metric_lookup (msg_meta.metric_id.name);
      if (map == NULL)
      {
        DEBUG ("gmond plugin: Not handling meta data %s.",
            msg_meta.metric_id.name);
        return (0);
      }

      ds = plugin_get_ds (map->type);
      if (ds == NULL)
      {
        WARNING ("gmond plugin: Could not find data set %s.", map->type);
        return (-1);
      }

      DEBUG ("gmond plugin: Received meta data for %s/%s.",
          msg_meta.metric_id.host, msg_meta.metric_id.name);

      pthread_mutex_lock (&staging_lock);
      se = staging_entry_get (msg_meta.metric_id.host,
          msg_meta.metric_id.name,
          map->type, map->type_instance,
          ds->ds_num);
      if (se != NULL)
        se->vl.interval = (int) msg_meta.metric.tmax;
      pthread_mutex_unlock (&staging_lock);

      if (se == NULL)
      {
        ERROR ("gmond plugin: staging_entry_get failed.");
        return (-1);
      }

      break;
    }

    default:
    {
      return (-1);
    }
  }

  return (0);
}