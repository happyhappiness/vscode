static int ds_get (char ***ret, /* {{{ */
    const data_set_t *ds, const value_list_t *vl,
    const rrdcreate_config_t *cfg)
{
  char **ds_def;
  int ds_num;

  char min[32];
  char max[32];
  char buffer[128];

  assert (ds->ds_num > 0);

  ds_def = malloc (ds->ds_num * sizeof (*ds_def));
  if (ds_def == NULL)
  {
    char errbuf[1024];
    ERROR ("rrdtool plugin: malloc failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }
  memset (ds_def, 0, ds->ds_num * sizeof (*ds_def));

  for (ds_num = 0; ds_num < ds->ds_num; ds_num++)
  {
    data_source_t *d = ds->ds + ds_num;
    char *type;
    int status;

    ds_def[ds_num] = NULL;

    if (d->type == DS_TYPE_COUNTER)
      type = "COUNTER";
    else if (d->type == DS_TYPE_GAUGE)
      type = "GAUGE";
    else if (d->type == DS_TYPE_DERIVE)
      type = "DERIVE";
    else if (d->type == DS_TYPE_ABSOLUTE)
      type = "ABSOLUTE";
    else
    {
      ERROR ("rrdtool plugin: Unknown DS type: %i",
          d->type);
      break;
    }

    if (isnan (d->min))
    {
      sstrncpy (min, "U", sizeof (min));
    }
    else
      ssnprintf (min, sizeof (min), "%f", d->min);

    if (isnan (d->max))
    {
      sstrncpy (max, "U", sizeof (max));
    }
    else
      ssnprintf (max, sizeof (max), "%f", d->max);

    status = ssnprintf (buffer, sizeof (buffer),
        "DS:%s:%s:%i:%s:%s",
        d->name, type,
        (cfg->heartbeat > 0)
        ? cfg->heartbeat
        : (int) CDTIME_T_TO_TIME_T (2 * vl->interval),
        min, max);
    if ((status < 1) || ((size_t) status >= sizeof (buffer)))
      break;

    ds_def[ds_num] = sstrdup (buffer);
  } /* for ds_num = 0 .. ds->ds_num */

  if (ds_num != ds->ds_num)
  {
    ds_free (ds_num, ds_def);
    return (-1);
  }

  if (ds_num <= 0)
  {
    sfree (ds_def);
    return (0);
  }

  *ret = ds_def;
  return (ds_num);
}