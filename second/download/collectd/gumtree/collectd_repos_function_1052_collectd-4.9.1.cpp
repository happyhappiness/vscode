static int tbl_shutdown (void)
{
	size_t i;

	for (i = 0; i < tables_num; ++i)
		tbl_clear (&tables[i]);
	sfree (tables);
	return 0;
}