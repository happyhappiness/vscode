int cu_rrd_create_file (const char *filename, /* {{{ */
    const data_set_t *ds, const value_list_t *vl,
    const rrdcreate_config_t *cfg)
{
  char **argv;
  int argc;
  char **rra_def;
  int rra_num;
  char **ds_def;
  int ds_num;
  int status = 0;
  time_t last_up;
  unsigned long stepsize;

  if (check_create_dir (filename))
    return (-1);

  if ((rra_num = rra_get (&rra_def, vl, cfg)) < 1)
  {
    ERROR ("cu_rrd_create_file failed: Could not calculate RRAs");
    return (-1);
  }

  if ((ds_num = ds_get (&ds_def, ds, vl, cfg)) < 1)
  {
    ERROR ("cu_rrd_create_file failed: Could not calculate DSes");
    return (-1);
  }

  argc = ds_num + rra_num;

  if ((argv = (char **) malloc (sizeof (char *) * (argc + 1))) == NULL)
  {
    char errbuf[1024];
    ERROR ("cu_rrd_create_file failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  memcpy (argv, ds_def, ds_num * sizeof (char *));
  memcpy (argv + ds_num, rra_def, rra_num * sizeof (char *));
  argv[ds_num + rra_num] = NULL;

  last_up = CDTIME_T_TO_TIME_T (vl->time);
  if (last_up <= 0)
    last_up = time (NULL);
  last_up -= 1;

  if (cfg->stepsize > 0)
    stepsize = cfg->stepsize;
  else
    stepsize = (unsigned long) CDTIME_T_TO_TIME_T (vl->interval);

  status = srrd_create (filename, stepsize, last_up,
      argc, (const char **) argv);

  free (argv);
  ds_free (ds_num, ds_def);
  rra_free (rra_num, rra_def);

  if (status != 0)
  {
    WARNING ("cu_rrd_create_file: srrd_create (%s) returned status %i.",
        filename, status);
  }
  else
  {
    DEBUG ("cu_rrd_create_file: Successfully created RRD file \"%s\".",
        filename);
  }

  return (status);
}