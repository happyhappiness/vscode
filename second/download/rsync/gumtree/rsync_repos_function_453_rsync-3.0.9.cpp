static int rsync_acl_get_perms(const rsync_acl *racl)
{
	return (racl->user_obj << 6)
	     + ((racl->mask_obj != NO_ENTRY ? racl->mask_obj : racl->group_obj) << 3)
	     + racl->other_obj;
}