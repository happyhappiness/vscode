static int cj_config_add_key (cj_t *db, /* {{{ */
                                   oconfig_item_t *ci)
{
  cj_key_t *key;
  int status;
  int i;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("curl_json plugin: The `Key' block "
             "needs exactly one string argument.");
    return (-1);
  }

  key = (cj_key_t *) malloc (sizeof (*key));
  if (key == NULL)
  {
    ERROR ("curl_json plugin: malloc failed.");
    return (-1);
  }
  memset (key, 0, sizeof (*key));
  key->magic = CJ_KEY_MAGIC;

  if (strcasecmp ("Key", ci->key) == 0)
  {
    status = cj_config_add_string ("Key", &key->path, ci);
    if (status != 0)
    {
      sfree (key);
      return (status);
    }
  }
  else
  {
    ERROR ("curl_json plugin: cj_config: "
           "Invalid key: %s", ci->key);
    return (-1);
  }

  status = 0;
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Type", child->key) == 0)
      status = cj_config_add_string ("Type", &key->type, child);
    else if (strcasecmp ("Instance", child->key) == 0)
      status = cj_config_add_string ("Instance", &key->instance, child);
    else
    {
      WARNING ("curl_json plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  while (status == 0)
  {
    if (key->type == NULL)
    {
      WARNING ("curl_json plugin: `Type' missing in `Key' block.");
      status = -1;
    }

    break;
  } /* while (status == 0) */

  /* store path in a tree that will match the json map structure, example:
   * "httpd/requests/count",
   * "httpd/requests/current" ->
   * { "httpd": { "requests": { "count": $key, "current": $key } } }
   */
  if (status == 0)
  {
    char *ptr;
    char *name;
    char ent[PATH_MAX];
    c_avl_tree_t *tree;

    if (db->tree == NULL)
      db->tree = cj_avl_create();

    tree = db->tree;
    name = key->path;
    ptr = key->path;
    if (*ptr == '/')
      ++ptr;

    name = ptr;
    while (*ptr)
    {
      if (*ptr == '/')
      {
        c_avl_tree_t *value;
        int len;

        len = ptr-name;
        if (len == 0)
          break;
        sstrncpy (ent, name, len+1);

        if (c_avl_get (tree, ent, (void *) &value) != 0)
        {
          value = cj_avl_create ();
          c_avl_insert (tree, strdup (ent), value);
        }

        tree = value;
        name = ptr+1;
      }
      ++ptr;
    }
    if (*name)
      c_avl_insert (tree, strdup(name), key);
    else
    {
      ERROR ("curl_json plugin: invalid key: %s", key->path);
      status = -1;
    }
  }

  return (status);
}