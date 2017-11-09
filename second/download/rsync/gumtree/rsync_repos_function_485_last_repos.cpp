static void rsync_acl_free(rsync_acl *racl)
{
	if (racl->names.idas)
		free(racl->names.idas);
	*racl = empty_rsync_acl;
}