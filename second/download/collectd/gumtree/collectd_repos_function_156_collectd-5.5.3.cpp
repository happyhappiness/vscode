static int cdbi_config_add_database (oconfig_item_t *ci) /* {{{ */
{
  cdbi_database_t *db;
  int status;
  int i;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("dbi plugin: The `Database' block "
        "needs exactly one string argument.");
    return (-1);
  }

  db = (cdbi_database_t *) malloc (sizeof (*db));
  if (db == NULL)
  {
    ERROR ("dbi plugin: malloc failed.");
    return (-1);
  }
  memset (db, 0, sizeof (*db));

  status = cf_util_get_string (ci, &db->name);
  if (status != 0)
  {
    sfree (db);
    return (status);
  }

  /* Fill the `cdbi_database_t' structure.. */
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Driver", child->key) == 0)
      status = cf_util_get_string (child, &db->driver);
    else if (strcasecmp ("DriverOption", child->key) == 0)
      status = cdbi_config_add_database_driver_option (db, child);
    else if (strcasecmp ("SelectDB", child->key) == 0)
      status = cf_util_get_string (child, &db->select_db);
    else if (strcasecmp ("Query", child->key) == 0)
      status = udb_query_pick_from_list (child, queries, queries_num,
          &db->queries, &db->queries_num);
    else if (strcasecmp ("Host", child->key) == 0)
      status = cf_util_get_string (child, &db->host);
    else
    {
      WARNING ("dbi plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  /* Check that all necessary options have been given. */
  while (status == 0)
  {
    if (db->driver == NULL)
    {
      WARNING ("dbi plugin: `Driver' not given for database `%s'", db->name);
      status = -1;
    }
    if (db->driver_options_num == 0)
    {
      WARNING ("dbi plugin: No `DriverOption' given for database `%s'. "
          "This will likely not work.", db->name);
    }

    break;
  } /* while (status == 0) */

  while ((status == 0) && (db->queries_num > 0))
  {
    db->q_prep_areas = (udb_query_preparation_area_t **) calloc (
        db->queries_num, sizeof (*db->q_prep_areas));

    if (db->q_prep_areas == NULL)
    {
      WARNING ("dbi plugin: malloc failed");
      status = -1;
      break;
    }

    for (i = 0; i < db->queries_num; ++i)
    {
      db->q_prep_areas[i]
        = udb_query_allocate_preparation_area (db->queries[i]);

      if (db->q_prep_areas[i] == NULL)
      {
        WARNING ("dbi plugin: udb_query_allocate_preparation_area failed");
        status = -1;
        break;
      }
    }

    break;
  }

  /* If all went well, add this database to the global list of databases. */
  if (status == 0)
  {
    cdbi_database_t **temp;

    temp = (cdbi_database_t **) realloc (databases,
        sizeof (*databases) * (databases_num + 1));
    if (temp == NULL)
    {
      ERROR ("dbi plugin: realloc failed");
      status = -1;
    }
    else
    {
      user_data_t ud;
      char *name = NULL;

      databases = temp;
      databases[databases_num] = db;
      databases_num++;

      memset (&ud, 0, sizeof (ud));
      ud.data = (void *) db;
      ud.free_func = NULL;
      name = ssnprintf_alloc("dbi:%s", db->name);

      plugin_register_complex_read (/* group = */ NULL,
          /* name = */ name ? name : db->name,
          /* callback = */ cdbi_read_database,
          /* interval = */ NULL,
          /* user_data = */ &ud);
      free (name);
    }
  }

  if (status != 0)
  {
    cdbi_database_free (db);
    return (-1);
  }

  return (0);
}