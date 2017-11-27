static int c_ipmi_config(oconfig_item_t *ci) {
  _Bool have_instance_block = 0;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Instance", child->key) == 0) {
      int status = c_ipmi_config_add_instance(child);
      if (status != 0)
        return status;

      have_instance_block = 1;
    } else if (!have_instance_block) {
      /* Non-instance option: Assume legacy configuration (without <Instance />
       * blocks) and call c_ipmi_config_add_instance with the <Plugin /> block.
       */
      WARNING("ipmi plugin: Legacy configuration found! Please update your "
              "config file.");
      return c_ipmi_config_add_instance(ci);
    } else {
      WARNING("ipmi plugin: The configuration option "
              "\"%s\" is not allowed here. Did you "
              "forget to add an <Instance /> block "
              "around the configuration?",
              child->key);
      return -1;
    }
  } /* for (ci->children) */

  return 0;
}