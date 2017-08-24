{
	const char	*accpath;
#if HAVE_SUN_ACL
	acl_t		*acl;
#else
	acl_t		acl;
#endif
	int		r;

	accpath = NULL;

#if HAVE_SUN_ACL || HAVE_DARWIN_ACL || HAVE_ACL_GET_FD_NP
	if (*fd < 0)
#else
	/* For default ACLs on Linux we need reachable accpath */
	if (*fd < 0 || S_ISDIR(archive_entry_mode(entry)))
#endif
	{
		accpath = archive_entry_sourcepath(entry);
		if (accpath == NULL || (a->tree != NULL &&
		    a->tree_enter_working_dir(a->tree) != 0))
			accpath = archive_entry_pathname(entry);
		if (accpath == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Couldn't determine file path to read ACLs");
			return (ARCHIVE_WARN);
		}
		if (a->tree != NULL &&
#if !HAVE_SUN_ACL && !HAVE_DARWIN_ACL && !HAVE_ACL_GET_FD_NP
		    *fd < 0 &&
#endif
		    (a->follow_symlinks ||
		    archive_entry_filetype(entry) != AE_IFLNK)) {
			*fd = a->open_on_current_dir(a->tree,
			    accpath, O_RDONLY | O_NONBLOCK);
		}
	}

	archive_entry_acl_clear(entry);

	acl = NULL;

#if HAVE_NFS4_ACL
	/* Try NFSv4 ACL first. */
	if (*fd >= 0)
#if HAVE_SUN_ACL
		/* Solaris reads both POSIX.1e and NFSv4 ACL here */
		facl_get(*fd, 0, &acl);
#elif HAVE_ACL_GET_FD_NP
		acl = acl_get_fd_np(*fd, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);
#else
		acl = acl_get_fd(*fd);
#endif
#if HAVE_ACL_GET_LINK_NP
	else if (!a->follow_symlinks)
		acl = acl_get_link_np(accpath, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);
#else
	else if ((!a->follow_symlinks)
	    && (archive_entry_filetype(entry) == AE_IFLNK))
		/* We can't get the ACL of a symlink, so we assume it can't
		   have one. */
		acl = NULL;
#endif
	else
#if HAVE_SUN_ACL
		/* Solaris reads both POSIX.1e and NFSv4 ACLs here */
		acl_get(accpath, 0, &acl);
#else
		acl = acl_get_file(accpath, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);
#endif


#if HAVE_ACL_IS_TRIVIAL_NP || HAVE_SUN_ACL
	/* Ignore "trivial" ACLs that just mirror the file mode. */
	if (acl != NULL) {
#if HAVE_SUN_ACL
		if (sun_acl_is_trivial(acl, archive_entry_mode(entry),
		    &r) == 0 && r == 1)
#elif HAVE_ACL_IS_TRIVIAL_NP
		if (acl_is_trivial_np(acl, &r) == 0 && r == 1)
#endif
		{
			acl_free(acl);
			acl = NULL;
			/*
			 * Simultaneous NFSv4 and POSIX.1e ACLs for the same
			 * entry are not allowed, so we should return here
			 */
			return (ARCHIVE_OK);
		}
	}
#endif	/* HAVE_ACL_IS_TRIVIAL_NP || HAVE_SUN_ACL */
	if (acl != NULL) {
		r = translate_acl(a, entry, acl, ARCHIVE_ENTRY_ACL_TYPE_NFS4);
		acl_free(acl);
		if (r != ARCHIVE_OK) {
			archive_set_error(&a->archive, errno,
			    "Couldn't translate "
#if !HAVE_SUN_ACL
			    "NFSv4 "
#endif
			    "ACLs");
		}
#if HAVE_DARWIN_ACL
		/*
		 * Because Mac OS doesn't support owner@, group@ and everyone@
		 * ACLs we need to add NFSv4 ACLs mirroring the file mode to
		 * the archive entry. Otherwise extraction on non-Mac platforms
		 * would lead to an invalid file mode.
		 */
		if ((archive_entry_acl_types(entry) &
		    ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0)
			add_trivial_nfs4_acl(entry);
#endif
		return (r);
	}
#endif	/* HAVE_NFS4_ACL */

#if HAVE_POSIX_ACL
	/* This code path is skipped on MacOS and Solaris */

	/* Retrieve access ACL from file. */
	if (*fd >= 0)
		acl = acl_get_fd(*fd);
#if HAVE_ACL_GET_LINK_NP
	else if (!a->follow_symlinks)
		acl = acl_get_link_np(accpath, ACL_TYPE_ACCESS);
#else
	else if ((!a->follow_symlinks)
	    && (archive_entry_filetype(entry) == AE_IFLNK))
		/* We can't get the ACL of a symlink, so we assume it can't
		   have one. */
		acl = NULL;
#endif
	else
		acl = acl_get_file(accpath, ACL_TYPE_ACCESS);

#if HAVE_ACL_IS_TRIVIAL_NP
	/* Ignore "trivial" ACLs that just mirror the file mode. */
	if (acl != NULL && acl_is_trivial_np(acl, &r) == 0) {
		if (r) {
			acl_free(acl);
			acl = NULL;
		}
	}
#endif

	if (acl != NULL) {
		r = translate_acl(a, entry, acl, ARCHIVE_ENTRY_ACL_TYPE_ACCESS);
		acl_free(acl);
		acl = NULL;
		if (r != ARCHIVE_OK) {
			archive_set_error(&a->archive, errno,
			    "Couldn't translate access ACLs");
			return (r);
		}
	}

	/* Only directories can have default ACLs. */
	if (S_ISDIR(archive_entry_mode(entry))) {
#if HAVE_ACL_GET_FD_NP
		if (*fd >= 0)
			acl = acl_get_fd_np(*fd, ACL_TYPE_DEFAULT);
		else
#endif
		acl = acl_get_file(accpath, ACL_TYPE_DEFAULT);
		if (acl != NULL) {
			r = translate_acl(a, entry, acl,
			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT);
			acl_free(acl);
			if (r != ARCHIVE_OK) {
				archive_set_error(&a->archive, errno,
				    "Couldn't translate default ACLs");
				return (r);
			}
		}
	}
#endif	/* HAVE_POSIX_ACL */
	return (ARCHIVE_OK);
}