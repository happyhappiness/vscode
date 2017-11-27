static int cjni_config_callback(oconfig_item_t *ci) /* {{{ */
{
  oconfig_item_t *ci_copy;
  oconfig_item_t *tmp;

  assert(ci != NULL);
  if (ci->children_num == 0)
    return (0); /* nothing to do */

  ci_copy = oconfig_clone(ci);
  if (ci_copy == NULL) {
    ERROR("java plugin: oconfig_clone failed.");
    return (-1);
  }

  if (config_block == NULL) {
    config_block = ci_copy;
    return (0);
  }

  tmp = realloc(config_block->children,
                (config_block->children_num + ci_copy->children_num) *
                    sizeof(*tmp));
  if (tmp == NULL) {
    ERROR("java plugin: realloc failed.");
    oconfig_free(ci_copy);
    return (-1);
  }
  config_block->children = tmp;

  /* Copy the pointers */
  memcpy(config_block->children + config_block->children_num, ci_copy->children,
         ci_copy->children_num * sizeof(*ci_copy->children));
  config_block->children_num += ci_copy->children_num;

  /* Delete the pointers from the copy, so `oconfig_free' can't free them. */
  memset(ci_copy->children, 0,
         ci_copy->children_num * sizeof(*ci_copy->children));
  ci_copy->children_num = 0;

  oconfig_free(ci_copy);

  return (0);
}