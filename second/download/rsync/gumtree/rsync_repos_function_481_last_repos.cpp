static rsync_acl *create_racl(void)
{
	rsync_acl *racl = new(rsync_acl);

	if (!racl)
		out_of_memory("create_racl");
	*racl = empty_rsync_acl;

	return racl;
}