static int rollback_single_pick(void)
{
	unsigned char head_sha1[20];

	if (!file_exists(git_path_cherry_pick_head()) &&
	    !file_exists(git_path_revert_head()))
		return error(_("no cherry-pick or revert in progress"));
	if (read_ref_full("HEAD", 0, head_sha1, NULL))
		return error(_("cannot resolve HEAD"));
	if (is_null_sha1(head_sha1))
		return error(_("cannot abort from a branch yet to be born"));
	return reset_for_rollback(head_sha1);
}