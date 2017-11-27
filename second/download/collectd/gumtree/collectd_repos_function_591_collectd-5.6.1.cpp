static int sensu_config(oconfig_item_t *ci) /* {{{ */
{
	oconfig_item_t	*child;
	int		 status;
	struct str_list sensu_tags_arr;

	sensu_tags_arr.nb_strs = 0;
	sensu_tags_arr.strs = NULL;

	for (int i = 0; i < ci->children_num; i++)  {
		child = &ci->children[i];

		if (strcasecmp("Node", child->key) == 0) {
			sensu_config_node(child);
		} else if (strcasecmp(child->key, "attribute") == 0) {
			if (child->values_num != 2) {
				WARNING("sensu attributes need both a key and a value.");
				continue;
			}
			if (child->values[0].type != OCONFIG_TYPE_STRING ||
					child->values[1].type != OCONFIG_TYPE_STRING) {
				WARNING("sensu attribute needs string arguments.");
				continue;
			}

			strarray_add(&sensu_attrs, &sensu_attrs_num, child->values[0].value.string);
			strarray_add(&sensu_attrs, &sensu_attrs_num, child->values[1].value.string);

			DEBUG("write_sensu plugin: New attribute: %s => %s",
					child->values[0].value.string,
					child->values[1].value.string);
		} else if (strcasecmp(child->key, "tag") == 0) {
			char *tmp = NULL;
			status = cf_util_get_string(child, &tmp);
			if (status != 0)
				continue;

			status = add_str_to_list(&sensu_tags_arr, tmp);
			sfree(tmp);
			if (status != 0)
				continue;
			DEBUG("write_sensu plugin: Got tag: %s", tmp);
		} else {
			WARNING("write_sensu plugin: Ignoring unknown "
				 "configuration option \"%s\" at top level.",
				 child->key);
		}
	}
	if (sensu_tags_arr.nb_strs > 0) {
		sfree (sensu_tags);
		sensu_tags = build_json_str_list("tags", &sensu_tags_arr);
		free_str_list(&sensu_tags_arr);
		if (sensu_tags == NULL) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return -1;
		}
	}
	return 0;
}