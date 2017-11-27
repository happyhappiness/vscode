static int cdbi_init (void) /* {{{ */
{
  static int did_init = 0;
  int status;

  if (did_init != 0)
    return (0);

  if (queries_num == 0)
  {
    ERROR ("dbi plugin: No <Query> blocks have been found. Without them, "
        "this plugin can't do anything useful, so we will returns an error.");
    return (-1);
  }

  if (databases_num == 0)
  {
    ERROR ("dbi plugin: No <Database> blocks have been found. Without them, "
        "this plugin can't do anything useful, so we will returns an error.");
    return (-1);
  }

  status = dbi_initialize (NULL);
  if (status < 0)
  {
    ERROR ("dbi plugin: cdbi_init: dbi_initialize failed with status %i.",
        status);
    return (-1);
  }
  else if (status == 0)
  {
    ERROR ("dbi plugin: `dbi_initialize' could not load any drivers. Please "
        "install at least one `DBD' or check your installation.");
    return (-1);
  }
  DEBUG ("dbi plugin: cdbi_init: dbi_initialize reports %i driver%s.",
      status, (status == 1) ? "" : "s");

  return (0);
}