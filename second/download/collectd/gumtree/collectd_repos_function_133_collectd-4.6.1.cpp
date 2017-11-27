static int rc_write (const data_set_t *ds, const value_list_t *vl)
{
  char filename[512];
  char values[512];
  char *values_array[2];
  int status;

  if (daemon_address == NULL)
  {
    ERROR ("rrdcached plugin: daemon_address == NULL.");
    plugin_unregister_write ("rrdcached");
    return (-1);
  }

  if (strcmp (ds->type, vl->type) != 0)
  {
    ERROR ("rrdcached plugin: DS type does not match value list type");
    return (-1);
  }

  if (value_list_to_filename (filename, sizeof (filename), ds, vl) != 0)
  {
    ERROR ("rrdcached plugin: value_list_to_filename failed.");
    return (-1);
  }

  if (value_list_to_string (values, sizeof (values), ds, vl) != 0)
  {
    ERROR ("rrdcached plugin: value_list_to_string failed.");
    return (-1);
  }

  values_array[0] = values;
  values_array[1] = NULL;

  if (config_create_files != 0)
  {
    struct stat statbuf;

    status = stat (filename, &statbuf);
    if (status != 0)
    {
      if (errno != ENOENT)
      {
        char errbuf[1024];
        ERROR ("rrdcached plugin: stat (%s) failed: %s",
            filename, sstrerror (errno, errbuf, sizeof (errbuf)));
        return (-1);
      }

      status = cu_rrd_create_file (filename, ds, vl, &rrdcreate_config);
      if (status != 0)
      {
        ERROR ("rrdcached plugin: cu_rrd_create_file (%s) failed.",
            filename);
        return (-1);
      }
    }
  }

  status = rrdc_connect (daemon_address);
  if (status != 0)
  {
    ERROR ("rrdcached plugin: rrdc_connect (%s) failed with status %i.",
        daemon_address, status);
    return (-1);
  }

  status = rrdc_update (filename, /* values_num = */ 1, (void *) values_array);
  if (status != 0)
  {
    ERROR ("rrdcached plugin: rrdc_update (%s, [%s], 1) failed with "
        "status %i.",
        filename, values_array[0], status);
    return (-1);
  }

  return (0);
}