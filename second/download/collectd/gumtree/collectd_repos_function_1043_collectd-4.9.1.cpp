static int tbl_config_result (tbl_t *tbl, oconfig_item_t *ci)
{
	tbl_result_t *res;

	int status = 0;
	size_t i;

	if (0 != ci->values_num) {
		log_err ("<Result> does not expect any arguments.");
		return 1;
	}

	res = (tbl_result_t *)realloc (tbl->results,
			(tbl->results_num + 1) * sizeof (*tbl->results));
	if (NULL == tbl) {
		char errbuf[1024];
		log_err ("realloc failed: %s.",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return -1;
	}

	tbl->results = res;
	++tbl->results_num;

	res = tbl->results + tbl->results_num - 1;
	tbl_result_setup (res);

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *c = ci->children + i;

		if (0 == strcasecmp (c->key, "Type"))
			tbl_config_set_s (c->key, &res->type, c);
		else if (0 == strcasecmp (c->key, "InstancePrefix"))
			tbl_config_set_s (c->key, &res->instance_prefix, c);
		else if (0 == strcasecmp (c->key, "InstancesFrom"))
			tbl_config_append_array_i (c->key,
					&res->instances, &res->instances_num, c);
		else if (0 == strcasecmp (c->key, "ValuesFrom"))
			tbl_config_append_array_i (c->key,
					&res->values, &res->values_num, c);
		else
			log_warn ("Ignoring unknown config key \"%s\" "
					" in <Result>.", c->key);
	}

	if (NULL == res->type) {
		log_err ("No \"Type\" option specified for <Result> "
				"in table \"%s\".", tbl->file);
		status = 1;
	}

	if (NULL == res->values) {
		log_err ("No \"ValuesFrom\" option specified for <Result> "
				"in table \"%s\".", tbl->file);
		status = 1;
	}

	if (0 != status) {
		tbl_result_clear (res);
		--tbl->results_num;
		return status;
	}
	return 0;
}