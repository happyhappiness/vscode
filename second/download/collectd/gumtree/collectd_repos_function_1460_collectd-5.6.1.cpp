static int tbl_shutdown (void)
{
	for (size_t i = 0; i < tables_num; ++i)
		tbl_clear (&tables[i]);
	sfree (tables);
	return 0;
}