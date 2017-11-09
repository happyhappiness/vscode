void init_hard_links(void)
{
	if (am_sender || protocol_version < 30)
		dev_tbl = hashtable_create(16, 1);
	else if (inc_recurse)
		prior_hlinks = hashtable_create(1024, 0);
}