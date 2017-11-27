static void parse_line (char *buf, size_t buf_len)
{
  char  *fields[64];
  size_t fields_num;
  data_set_t *ds;
  int i;

  fields_num = strsplit (buf, fields, 64);
  if (fields_num < 2)
    return;

  ds = (data_set_t *) malloc (sizeof (data_set_t));
  if (ds == NULL)
    return;

  memset (ds, '\0', sizeof (data_set_t));

  strncpy (ds->type, fields[0], sizeof (ds->type));
  ds->type[sizeof (ds->type) - 1] = '\0';

  ds->ds_num = fields_num - 1;
  ds->ds = (data_source_t *) calloc (ds->ds_num, sizeof (data_source_t));
  if (ds->ds == NULL)
    return;

  for (i = 0; i < ds->ds_num; i++)
    if (parse_ds (ds->ds + i, fields[i + 1], strlen (fields[i + 1])) != 0)
    {
      sfree (ds->ds);
      ERROR ("types_list: parse_line: Cannot parse data source #%i "
	  "of data set %s", i, ds->type);
      return;
    }

  DEBUG ("parse_line: ds = {%s, %i, %p};",
      ds->type, ds->ds_num, (void *) ds->ds);

  plugin_register_data_set (ds);

  sfree (ds->ds);
  sfree (ds);
}