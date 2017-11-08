static void rsync_acl_fake_perms(rsync_acl *racl, mode_t mode)
{
	racl->user_obj = (mode >> 6) & 7;
	racl->group_obj = (mode >> 3) & 7;
	racl->other_obj = mode & 7;
}