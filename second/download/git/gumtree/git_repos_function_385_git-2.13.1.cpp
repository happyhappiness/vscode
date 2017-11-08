static unsigned long get_shared_index_expire_date(void)
{
	static unsigned long shared_index_expire_date;
	static int shared_index_expire_date_prepared;

	if (!shared_index_expire_date_prepared) {
		git_config_get_expiry("splitindex.sharedindexexpire",
				      &shared_index_expire);
		shared_index_expire_date = approxidate(shared_index_expire);
		shared_index_expire_date_prepared = 1;
	}

	return shared_index_expire_date;
}