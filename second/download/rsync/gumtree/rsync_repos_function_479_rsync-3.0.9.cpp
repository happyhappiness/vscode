void uncache_tmp_acls(void)
{
	if (prior_access_count != (size_t)-1) {
		uncache_duo_acls(&access_acl_list, prior_access_count);
		prior_access_count = (size_t)-1;
	}

	if (prior_default_count != (size_t)-1) {
		uncache_duo_acls(&default_acl_list, prior_default_count);
		prior_default_count = (size_t)-1;
	}
}