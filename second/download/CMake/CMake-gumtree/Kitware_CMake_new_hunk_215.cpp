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
