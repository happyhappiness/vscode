static int o_config_add_database (oconfig_item_t *ci) /* {{{ */
{
  o_database_t *db;
  int status;
  int i;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("oracle plugin: The `Database' block "
        "needs exactly one string argument.");
    return (-1);
  }

  db = (o_database_t *) malloc (sizeof (*db));
  if (db == NULL)
  {
    ERROR ("oracle plugin: malloc failed.");
    return (-1);
  }
  memset (db, 0, sizeof (*db));

  status = o_config_set_string (&db->name, ci);
  if (status != 0)
  {
    sfree (db);
    return (status);
  }

  /* Fill the `o_database_t' structure.. */
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("ConnectID", child->key) == 0)
      status = o_config_set_string (&db->connect_id, child);
    else if (strcasecmp ("Username", child->key) == 0)
      status = o_config_set_string (&db->username, child);
    else if (strcasecmp ("Password", child->key) == 0)
      status = o_config_set_string (&db->password, child);
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

  /* If all went well, add this query to the list of queries within the
   * database structure. */
  if (status == 0)
  {
    o_database_t **temp;

    temp = (o_database_t **) realloc (databases,
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