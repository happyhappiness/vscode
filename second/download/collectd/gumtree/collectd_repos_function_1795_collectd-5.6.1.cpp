static int o_config_add_database (oconfig_item_t *ci) /* {{{ */
{
  o_database_t *db;
  int status;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("oracle plugin: The `Database' block "
        "needs exactly one string argument.");
    return (-1);
  }

  db = calloc (1, sizeof (*db));
  if (db == NULL)
  {
    ERROR ("oracle plugin: calloc failed.");
    return (-1);
  }
  db->name = NULL;
  db->host = NULL;
  db->connect_id = NULL;
  db->username = NULL;
  db->password = NULL;

  status = cf_util_get_string (ci, &db->name);
  if (status != 0)
  {
    sfree (db);
    return (status);
  }

  /* Fill the `o_database_t' structure.. */
  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("ConnectID", child->key) == 0)
      status = cf_util_get_string (child, &db->connect_id);
    else if (strcasecmp ("Host", child->key) == 0)
      status = cf_util_get_string (child, &db->host);
    else if (strcasecmp ("Username", child->key) == 0)
      status = cf_util_get_string (child, &db->username);
    else if (strcasecmp ("Password", child->key) == 0)
      status = cf_util_get_string (child, &db->password);
    else if (strcasecmp ("Query", child->key) == 0)
      status = udb_query_pick_from_list (child, queries, queries_num,
          &db->queries, &db->queries_num);
    else
    {
      WARNING ("oracle plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  /* Check that all necessary options have been given. */
  while (status == 0)
  {
    if (db->connect_id == NULL)
    {
      WARNING ("oracle plugin: `ConnectID' not given for query `%s'", db->name);
      status = -1;
    }
    if (db->username == NULL)
    {
      WARNING ("oracle plugin: `Username' not given for query `%s'", db->name);
      status = -1;
    }
    if (db->password == NULL)
    {
      WARNING ("oracle plugin: `Password' not given for query `%s'", db->name);
      status = -1;
    }

    break;
  } /* while (status == 0) */

  while ((status == 0) && (db->queries_num > 0))
  {
    db->q_prep_areas = (udb_query_preparation_area_t **) calloc (
        db->queries_num, sizeof (*db->q_prep_areas));

    if (db->q_prep_areas == NULL)
    {
      WARNING ("oracle plugin: calloc failed");
      status = -1;
      break;
    }

    for (int i = 0; i < db->queries_num; ++i)
    {
      db->q_prep_areas[i]
        = udb_query_allocate_preparation_area (db->queries[i]);

      if (db->q_prep_areas[i] == NULL)
      {
        WARNING ("oracle plugin: udb_query_allocate_preparation_area failed");
        status = -1;
        break;
      }
    }

    break;
  }

  /* If all went well, add this query to the list of queries within the
   * database structure. */
  if (status == 0)
  {
    o_database_t **temp;

    temp = realloc (databases,
        sizeof (*databases) * (databases_num + 1));
    if (temp == NULL)
    {
      ERROR ("oracle plugin: realloc failed");
      status = -1;
    }
    else
    {
      databases = temp;
      databases[databases_num] = db;
      databases_num++;
    }
  }

  if (status != 0)
  {
    o_database_free (db);
    return (-1);
  }

  return (0);
}