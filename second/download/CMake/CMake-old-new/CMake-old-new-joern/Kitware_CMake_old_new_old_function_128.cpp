static int
setup_acls(struct archive_read_disk *a,
    struct archive_entry *entry, int *fd)
{
	const char	*accpath;
	acl_t		 acl;
#if HAVE_ACL_IS_TRIVIAL_NP
	int		r;
#endif

	accpath = archive_entry_sourcepath(entry);
	if (accpath == NULL)
		accpath = archive_entry_pathname(entry);

	archive_entry_acl_clear(entry);

#ifdef ACL_TYPE_NFS4
	/* Try NFS4 ACL first. */
	if (*fd >= 0)
		acl = acl_get_fd(*fd);
#if HAVE_ACL_GET_LINK_NP
	else if (!a->follow_symlinks)
		acl = acl_get_link_np(accpath, ACL_TYPE_NFS4);
#else
	else if ((!a->follow_symlinks)
	    && (archive_entry_filetype(entry) == AE_IFLNK))
		/* We can't get the ACL of a symlink, so we assume it can't
		   have one. */
		acl = NULL;
#endif
	else
		acl = acl_get_file(accpath, ACL_TYPE_NFS4);
#if HAVE_ACL_IS_TRIVIAL_NP
	/* Ignore "trivial" ACLs that just mirror the file mode. */
	acl_is_trivial_np(acl, &r);
	if (r) {
		acl_free(acl);
		acl = NULL;
	}
#endif
	if (acl != NULL) {
		translate_acl(a, entry, acl, ARCHIVE_ENTRY_ACL_TYPE_NFS4);
		acl_free(acl);
		return (ARCHIVE_OK);
	}
#endif

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
	if (acl != NULL) {
		translate_acl(a, entry, acl,
		    ARCHIVE_ENTRY_ACL_TYPE_ACCESS);
		acl_free(acl);
	}

	/* Only directories can have default ACLs. */
	if (S_ISDIR(archive_entry_mode(entry))) {
		acl = acl_get_file(accpath, ACL_TYPE_DEFAULT);
		if (acl != NULL) {
			translate_acl(a, entry, acl,
			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT);
			acl_free(acl);
		}
	}
	return (ARCHIVE_OK);
}