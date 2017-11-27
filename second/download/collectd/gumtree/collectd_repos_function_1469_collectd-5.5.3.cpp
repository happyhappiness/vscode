static int riemann_config(oconfig_item_t *ci) /* {{{ */
{
	int		 i;
	oconfig_item_t	*child;
	int		 status;

	for (i = 0; i < ci->children_num; i++)  {
		child = &ci->children[i];

		if (strcasecmp("Node", child->key) == 0) {
			riemann_config_node (child);
		} else if (strcasecmp(child->key, "attribute") == 0) {
			char *key = NULL;
			char *val = NULL;

			if (child->values_num != 2) {
				WARNING("riemann attributes need both a key and a value.");
				return (-1);
			}
			if (child->values[0].type != OCONFIG_TYPE_STRING ||
			    child->values[1].type != OCONFIG_TYPE_STRING) {
				WARNING("riemann attribute needs string arguments.");
				return (-1);
			}
			if ((key = strdup(child->values[0].value.string)) == NULL) {
				WARNING("cannot allocate memory for attribute key.");
				return (-1);
			}
			if ((val = strdup(child->values[1].value.string)) == NULL) {
				WARNING("cannot allocate memory for attribute value.");
				sfree (key);
				return (-1);
			}
			strarray_add(&riemann_attrs, &riemann_attrs_num, key);
			strarray_add(&riemann_attrs, &riemann_attrs_num, val);
			DEBUG("write_riemann: got attr: %s => %s", key, val);
			sfree(key);
			sfree(val);
		} else if (strcasecmp(child->key, "tag") == 0) {
			char *tmp = NULL;
			status = cf_util_get_string(child, &tmp);
			if (status != 0)
				continue;

			strarray_add (&riemann_tags, &riemann_tags_num, tmp);
			DEBUG("write_riemann plugin: Got tag: %s", tmp);
			sfree (tmp);
		} else {
			WARNING ("write_riemann plugin: Ignoring unknown "
				 "configuration option \"%s\" at top level.",
				 child->key);
		}
	}
	return (0);
}