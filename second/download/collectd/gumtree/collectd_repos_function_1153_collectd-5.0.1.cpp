static int tbl_read (void)
{
	int status = -1;
	size_t i;

	if (0 == tables_num)
		return 0;

	for (i = 0; i < tables_num; ++i) {
		tbl_t *tbl = tables + i;

		if (0 != tbl_prepare (tbl)) {
			log_err ("Failed to prepare and parse table \"%s\".", tbl->file);
			continue;
		}

		if (0 == tbl_read_table (tbl))
			status = 0;

		tbl_finish (tbl);
	}
	return status;
}