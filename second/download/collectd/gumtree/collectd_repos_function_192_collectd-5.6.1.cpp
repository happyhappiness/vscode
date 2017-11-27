static void ds_free (int ds_num, char **ds_def) /* {{{ */
{
  for (int i = 0; i < ds_num; i++)
    if (ds_def[i] != NULL)
      free (ds_def[i]);
  free (ds_def);
}