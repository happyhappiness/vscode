int default_perms_for_dir(const char *dir)
{
	rsync_acl racl;
	SMB_ACL_T sacl;
	BOOL ok;
	int perms;

	if (dir == NULL)
		dir = ".";
	perms = ACCESSPERMS & ~orig_umask;
	/* Read the directory's default ACL.  If it has none, this will successfully return an empty ACL. */
	sacl = sys_acl_get_file(dir, SMB_ACL_TYPE_DEFAULT);
	if (sacl == NULL) {
		/* Couldn't get an ACL.  Darn. */
		switch (errno) {
		case EINVAL:
			/* If SMB_ACL_TYPE_DEFAULT isn't valid, then the ACLs must be non-POSIX. */
			break;
#ifdef ENOTSUP
		case ENOTSUP:
#endif
		case ENOSYS:
			/* No ACLs are available. */
			break;
		case ENOENT:
			if (dry_run) {
				/* We're doing a dry run, so the containing directory
				 * wasn't actually created.  Don't worry about it. */
				break;
			}
			/* Otherwise fall through. */
		default:
			rprintf(FWARNING,
				"default_perms_for_dir: sys_acl_get_file(%s, %s): %s, falling back on umask\n",
				dir, str_acl_type(SMB_ACL_TYPE_DEFAULT), strerror(errno));
		}
		return perms;
	}

	/* Convert it. */
	racl = empty_rsync_acl;
	ok = unpack_smb_acl(sacl, &racl);
	sys_acl_free_acl(sacl);
	if (!ok) {
		rprintf(FWARNING, "default_perms_for_dir: unpack_smb_acl failed, falling back on umask\n");
		return perms;
	}

	/* Apply the permission-bit entries of the default ACL, if any. */
	if (racl.user_obj != NO_ENTRY) {
		perms = rsync_acl_get_perms(&racl);
		if (DEBUG_GTE(ACL, 1))
			rprintf(FINFO, "got ACL-based default perms %o for directory %s\n", perms, dir);
	}

	rsync_acl_free(&racl);
	return perms;
}