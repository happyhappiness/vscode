static int cf_include_all(oconfig_item_t *root, int depth) {
  for (int i = 0; i < root->children_num; i++) {
    oconfig_item_t *new;
    oconfig_item_t *old;

    char *pattern = NULL;

    if (strcasecmp(root->children[i].key, "Include") != 0)
      continue;

    old = root->children + i;

    if ((old->values_num != 1) ||
        (old->values[0].type != OCONFIG_TYPE_STRING)) {
      ERROR("configfile: `Include' needs exactly one string argument.");
      continue;
    }

    for (int j = 0; j < old->children_num; ++j) {
      oconfig_item_t *child = old->children + j;

      if (strcasecmp(child->key, "Filter") == 0)
        cf_util_get_string(child, &pattern);
      else
        ERROR("configfile: Option `%s' not allowed in <Include> block.",
              child->key);
    }

    new = cf_read_generic(old->values[0].value.string, pattern, depth + 1);
    sfree(pattern);

    if (new == NULL)
      return (-1);

    /* Now replace the i'th child in `root' with `new'. */
    if (cf_ci_replace_child(root, new, i) < 0) {
      sfree(new->values);
      sfree(new);
      return (-1);
    }

    /* ... and go back to the new i'th child. */
    --i;

    sfree(new->values);
    sfree(new);
  } /* for (i = 0; i < root->children_num; i++) */

  return (0);
}