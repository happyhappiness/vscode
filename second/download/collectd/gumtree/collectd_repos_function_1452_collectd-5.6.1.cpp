static int tbl_config_table (oconfig_item_t *ci)
{
	tbl_t *tbl;

	int status = 0;

	if ((1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("<Table> expects a single string argument.");
		return 1;
	}

	tbl = realloc (tables, (tables_num + 1) * sizeof (*tables));
	if (NULL == tbl) {
		char errbuf[1024];
		log_err ("realloc failed: %s.",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return -1;
	}

	tables = tbl;
	++tables_num;

	tbl = tables + tables_num - 1;
	tbl_setup (tbl, ci->values[0].value.string);

	for (size_t i = 0; i < ((size_t) ci->children_num); ++i) {
		oconfig_item_t *c = ci->children + i;

		if (0 == strcasecmp (c->key, "Separator"))
			tbl_config_set_s (c->key, &tbl->sep, c);
		else if (0 == strcasecmp (c->key, "Instance"))
			tbl_config_set_s (c->key, &tbl->instance, c);
		else if (0 == strcasecmp (c->key, "Result"))
			tbl_config_result (tbl, c);
		else
			log_warn ("Ignoring unknown config key \"%s\" "
					"in <Table %s>.", c->key, tbl->file);
	}

	if (NULL == tbl->sep) {
		log_err ("Table \"%s\" does not specify any separator.", tbl->file);
		status = 1;
	} else {
		strunescape (tbl->sep, strlen (tbl->sep) + 1);
	}

	if (NULL == tbl->instance) {
		tbl->instance = sstrdup (tbl->file);
		replace_special (tbl->instance, strlen (tbl->instance));
	}

	if (NULL == tbl->results) {
		log_err ("Table \"%s\" does not specify any (valid) results.",
				tbl->file);
		status = 1;
	}

	if (0 != status) {
		tbl_clear (tbl);
		--tables_num;
		return status;
	}

	for (size_t i = 0; i < tbl->results_num; ++i) {
		tbl_result_t *res = tbl->results + i;

		for (size_t j = 0; j < res->instances_num; ++j)
			if (res->instances[j] > tbl->max_colnum)
				tbl->max_colnum = res->instances[j];

		for (size_t j = 0; j < res->values_num; ++j)
			if (res->values[j] > tbl->max_colnum)
				tbl->max_colnum = res->values[j];
	}
	return 0;
}