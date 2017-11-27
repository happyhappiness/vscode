static int cx_config_add_namespace (cx_t *db, /* {{{ */
    oconfig_item_t *ci)
{
  cx_namespace_t *ns;

  if ((ci->values_num != 2)
      || (ci->values[0].type != OCONFIG_TYPE_STRING)
      || (ci->values[1].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("curl_xml plugin: The `Namespace' option "
             "needs exactly two string arguments.");
    return (EINVAL);
  }

  ns = realloc (db->namespaces, sizeof (*db->namespaces)
      * (db->namespaces_num + 1));
  if (ns == NULL)
  {
    ERROR ("curl_xml plugin: realloc failed.");
    return (ENOMEM);
  }
  db->namespaces = ns;
  ns = db->namespaces + db->namespaces_num;
  memset (ns, 0, sizeof (*ns));

  ns->prefix = strdup (ci->values[0].value.string);
  ns->url = strdup (ci->values[1].value.string);

  if ((ns->prefix == NULL) || (ns->url == NULL))
  {
    sfree (ns->prefix);
    sfree (ns->url);
    ERROR ("curl_xml plugin: strdup failed.");
    return (ENOMEM);
  }

  db->namespaces_num++;
  return (0);
}