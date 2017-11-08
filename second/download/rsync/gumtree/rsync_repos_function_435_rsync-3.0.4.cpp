static void rsync_acl_strip_perms(rsync_acl *racl)
{
	racl->user_obj = NO_ENTRY;
	if (racl->mask_obj == NO_ENTRY)
		racl->group_obj = NO_ENTRY;
	else {
		if (racl->group_obj == racl->mask_obj)
			racl->group_obj = NO_ENTRY;
		racl->mask_obj = NO_ENTRY;
	}
	racl->other_obj = NO_ENTRY;
}