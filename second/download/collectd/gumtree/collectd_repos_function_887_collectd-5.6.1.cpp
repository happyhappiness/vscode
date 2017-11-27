static int memcached_config (oconfig_item_t *ci)
{
  int status = 0;
  _Bool have_instance_block = 0;

  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Instance", child->key) == 0)
    {
      config_add_instance (child);
      have_instance_block = 1;
    }
    else if (!have_instance_block)
    {
      /* Non-instance option: Assume legacy configuration (without <Instance />
       * blocks) and call config_add_instance() with the <Plugin /> block. */
      return (config_add_instance (ci));
    }
    else
      WARNING ("memcached plugin: The configuration option "
          "\"%s\" is not allowed here. Did you "
          "forget to add an <Instance /> block "
          "around the configuration?",
          child->key);
  } /* for (ci->children) */

  return (status);
}