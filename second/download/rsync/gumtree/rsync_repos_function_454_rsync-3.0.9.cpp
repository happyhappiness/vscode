static void rsync_acl_strip_perms(stat_x *sxp)
{
	rsync_acl *racl = sxp->acc_acl;

	racl->user_obj = NO_ENTRY;
	if (racl->mask_obj == NO_ENTRY)
		racl->group_obj = NO_ENTRY;
	else {
		int group_perms = (sxp->st.st_mode >> 3) & 7;
		if (racl->group_obj == group_perms)
			racl->group_obj = NO_ENTRY;
#ifndef HAVE_SOLARIS_ACLS
		if (racl->names.count != 0 && racl->mask_obj == group_perms)
			racl->mask_obj = NO_ENTRY;
#endif
	}
	racl->other_obj = NO_ENTRY;
}