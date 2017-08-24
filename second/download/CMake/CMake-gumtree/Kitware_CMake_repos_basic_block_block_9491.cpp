{
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