static int calc_sacl_entries(const rsync_acl *racl)
{
	/* A System ACL always gets user/group/other permission entries. */
	return racl->names.count
#ifdef ACLS_NEED_MASK
	     + 4;
#else
	     + (racl->mask_obj != NO_ENTRY) + 3;
#endif
}