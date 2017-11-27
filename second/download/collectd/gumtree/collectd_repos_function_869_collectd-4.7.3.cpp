static void tbl_clear (tbl_t *tbl)
{
	size_t i;

	sfree (tbl->file);
	sfree (tbl->sep);
	sfree (tbl->instance);

	for (i = 0; i < tbl->results_num; ++i)
		tbl_result_clear (tbl->results + i);
	sfree (tbl->results);
	tbl->results_num = 0;

	tbl->max_colnum  = 0;
}