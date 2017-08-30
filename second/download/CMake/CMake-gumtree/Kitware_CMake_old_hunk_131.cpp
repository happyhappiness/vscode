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
