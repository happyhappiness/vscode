(acl_set(name, acl) != 0)
#elif HAVE_ACL_SET_LINK_NP
	if (acl_set_link_np(name, acl_type, acl) != 0)
#else
	/* TODO: Skip this if 'name' is a symlink. */
	if (acl_set_file(name, acl_type, acl) != 0)
#endif
	{
		if (errno == EOPNOTSUPP) {
			/* Filesystem doesn't support ACLs */
			ret = ARCHIVE_OK;
		} else {
			archive_set_error(a, errno, "Failed to set %s acl",
			    tname);
			ret = ARCHIVE_WARN;
		}
	}