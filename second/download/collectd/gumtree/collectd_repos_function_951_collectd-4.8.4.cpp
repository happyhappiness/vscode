static int tbl_finish (tbl_t *tbl)
{
	size_t i;

	for (i = 0; i < tbl->results_num; ++i)
		tbl->results[i].ds = NULL;
	return 0;
}