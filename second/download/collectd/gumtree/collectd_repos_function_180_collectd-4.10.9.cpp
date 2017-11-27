static int rc_read (void)
{
  int status;
  rrdc_stats_t *head;
  rrdc_stats_t *ptr;

  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  if (daemon_address == NULL)
    return (-1);

  if (config_collect_stats == 0)
    return (-1);

  vl.values = values;
  vl.values_len = 1;

  if ((strncmp ("unix:", daemon_address, strlen ("unix:")) == 0)
      || (daemon_address[0] == '/'))
    sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  else
    sstrncpy (vl.host, daemon_address, sizeof (vl.host));
  sstrncpy (vl.plugin, "rrdcached", sizeof (vl.plugin));

  head = NULL;
  status = rrdc_stats_get (&head);
  if (status != 0)
  {
    ERROR ("rrdcached plugin: rrdc_stats_get failed with status %i.", status);
    return (-1);
  }

  for (ptr = head; ptr != NULL; ptr = ptr->next)
  {
    if (ptr->type == RRDC_STATS_TYPE_GAUGE)
      values[0].gauge = (gauge_t) ptr->value.gauge;
    else if (ptr->type == RRDC_STATS_TYPE_COUNTER)
      values[0].counter = (counter_t) ptr->value.counter;
    else
      continue;

    if (strcasecmp ("QueueLength", ptr->name) == 0)
    {
      sstrncpy (vl.type, "queue_length", sizeof (vl.type));
      sstrncpy (vl.type_instance, "", sizeof (vl.type_instance));
    }
    else if (strcasecmp ("UpdatesWritten", ptr->name) == 0)
    {
      sstrncpy (vl.type, "operations", sizeof (vl.type));
      sstrncpy (vl.type_instance, "write-updates", sizeof (vl.type_instance));
    }
    else if (strcasecmp ("DataSetsWritten", ptr->name) == 0)
    {
      sstrncpy (vl.type, "operations", sizeof (vl.type));
      sstrncpy (vl.type_instance, "write-data_sets",
          sizeof (vl.type_instance));
    }
    else if (strcasecmp ("TreeNodesNumber", ptr->name) == 0)
    {
      sstrncpy (vl.type, "gauge", sizeof (vl.type));
      sstrncpy (vl.type_instance, "tree_nodes", sizeof (vl.type_instance));
    }
    else if (strcasecmp ("TreeDepth", ptr->name) == 0)
    {
      sstrncpy (vl.type, "gauge", sizeof (vl.type));
      sstrncpy (vl.type_instance, "tree_depth", sizeof (vl.type_instance));
    }
    else if (strcasecmp ("FlushesReceived", ptr->name) == 0)
    {
      sstrncpy (vl.type, "operations", sizeof (vl.type));
      sstrncpy (vl.type_instance, "receive-flush", sizeof (vl.type_instance));
    }
    else if (strcasecmp ("JournalBytes", ptr->name) == 0)
    {
      sstrncpy (vl.type, "counter", sizeof (vl.type));
      sstrncpy (vl.type_instance, "journal-bytes", sizeof (vl.type_instance));
    }
    else if (strcasecmp ("JournalRotate", ptr->name) == 0)
    {
      sstrncpy (vl.type, "counter", sizeof (vl.type));
      sstrncpy (vl.type_instance, "journal-rotates", sizeof (vl.type_instance));
    }
    else if (strcasecmp ("UpdatesReceived", ptr->name) == 0)
    {
      sstrncpy (vl.type, "operations", sizeof (vl.type));
      sstrncpy (vl.type_instance, "receive-update", sizeof (vl.type_instance));
    }
    else
    {
      DEBUG ("rrdcached plugin: rc_read: Unknown statistic `%s'.", ptr->name);
      continue;
    }

    plugin_dispatch_values (&vl);
  } /* for (ptr = head; ptr != NULL; ptr = ptr->next) */

  rrdc_stats_free (head);

  return (0);
}