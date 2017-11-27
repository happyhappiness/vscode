static int cx_config_add_xpath (cx_t *db, oconfig_item_t *ci) /* {{{ */
{
  cx_xpath_t *xpath;
  char *name;
  llentry_t *le;
  int status;
  int i;

  xpath = malloc (sizeof (*xpath));
  if (xpath == NULL)
  {
    ERROR ("curl_xml plugin: malloc failed.");
    return (-1);
  }
  memset (xpath, 0, sizeof (*xpath));

  status = cf_util_get_string (ci, &xpath->path);
  if (status != 0)
  {
    cx_xpath_free (xpath);
    return (status);
  }

  /* error out if xpath->path is an empty string */
  if (strlen (xpath->path) == 0)
  {
    ERROR ("curl_xml plugin: invalid xpath. "
           "xpath value can't be an empty string");
    cx_xpath_free (xpath);
    return (-1);
  }

  status = 0;
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Type", child->key) == 0)
      status = cf_util_get_string (child, &xpath->type);
    else if (strcasecmp ("InstancePrefix", child->key) == 0)
      status = cf_util_get_string (child, &xpath->instance_prefix);
    else if (strcasecmp ("InstanceFrom", child->key) == 0)
      status = cf_util_get_string (child, &xpath->instance);
    else if (strcasecmp ("ValuesFrom", child->key) == 0)
      status = cx_config_add_values ("ValuesFrom", xpath, child);
    else
    {
      WARNING ("curl_xml plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  if (status != 0)
  {
    cx_xpath_free (xpath);
    return status;
  }

  if (xpath->type == NULL)
  {
    WARNING ("curl_xml plugin: `Type' missing in `xpath' block.");
    cx_xpath_free (xpath);
    return -1;
  }

  if (db->list == NULL)
  {
    db->list = llist_create();
    if (db->list == NULL)
    {
      ERROR ("curl_xml plugin: list creation failed.");
      cx_xpath_free (xpath);
      return (-1);
    }
  }

  name = strdup (xpath->path);
  if (name == NULL)
  {
    ERROR ("curl_xml plugin: strdup failed.");
    cx_xpath_free (xpath);
    return (-1);
  }

  le = llentry_create (name, xpath);
  if (le == NULL)
  {
    ERROR ("curl_xml plugin: llentry_create failed.");
    cx_xpath_free (xpath);
    sfree (name);
    return (-1);
  }

  llist_append (db->list, le);
  return (0);
}