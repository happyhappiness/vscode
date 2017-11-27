static int cdbi_read (void) /* {{{ */
{
  size_t i;
  int success = 0;
  int status;

  for (i = 0; i < databases_num; i++)
  {
    status = cdbi_read_database (databases[i]);
    if (status == 0)
      success++;
  }

  if (success == 0)
  {
    ERROR ("dbi plugin: No database could be read. Will return an error so "
        "the plugin will be delayed.");
    return (-1);
  }

  return (0);
}