static void parse_line (char *buf)
{
  char  *fields[64];
  size_t fields_num;
  data_set_t *ds;

  fields_num = strsplit (buf, fields, 64);
  if (fields_num < 2)
    return;

  /* Ignore lines which begin with a hash sign. */
  if (fields[0][0] == '#')
    return;

  ds = calloc (1, sizeof (*ds));
  if (ds == NULL)
    return;

  sstrncpy (ds->type, fields[0], sizeof (ds->type));

  ds->ds_num = fields_num - 1;
  ds->ds = (data_source_t *) calloc (ds->ds_num, sizeof (data_source_t));
  if (ds->ds == NULL)
  {
    sfree (ds);
    return;
  }

  for (size_t i = 0; i < ds->ds_num; i++)
    if (parse_ds (ds->ds + i, fields[i + 1], strlen (fields[i + 1])) != 0)
    {
      ERROR ("types_list: parse_line: Cannot parse data source #%zu "
	  "of data set %s", i, ds->type);
      sfree (ds->ds);
      sfree (ds);
      return;
    }

  plugin_register_data_set (ds);

  sfree (ds->ds);
  sfree (ds);
}