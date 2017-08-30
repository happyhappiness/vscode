					    ae_id, ae_name);

		s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
#if !HAVE_DARWIN_ACL
		if (s == -1) {
			archive_set_error(&a->archive, errno,
			    "Failed to get next ACL entry");
			return (ARCHIVE_WARN);
		}
#endif
	}
	return (ARCHIVE_OK);
}
#endif	/* !HAVE_SUN_ACL */
#else	/* !HAVE_POSIX_ACL && !HAVE_NFS4_ACL */
static int
setup_acls(struct archive_read_disk *a,
    struct archive_entry *entry, int *fd)
