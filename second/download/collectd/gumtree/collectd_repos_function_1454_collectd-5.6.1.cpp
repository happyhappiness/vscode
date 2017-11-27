static int tbl_prepare (tbl_t *tbl)
{
	for (size_t i = 0; i < tbl->results_num; ++i) {
		tbl_result_t *res = tbl->results + i;

		res->ds = plugin_get_ds (res->type);
		if (NULL == res->ds) {
			log_err ("Unknown type \"%s\". See types.db(5) for details.",
					res->type);
			return -1;
		}

		if (res->values_num != res->ds->ds_num) {
			log_err ("Invalid type \"%s\". Expected %zu data source%s, "
					"got %zu.", res->type, res->values_num,
					(1 == res->values_num) ? "" : "s",
					res->ds->ds_num);
			return -1;
		}
	}
	return 0;
}