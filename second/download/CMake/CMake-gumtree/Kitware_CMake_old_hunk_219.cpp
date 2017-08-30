					    ae_id, ae_name);

		s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
	}
	return (ARCHIVE_OK);
}
#else
static int
setup_acls(struct archive_read_disk *a,
    struct archive_entry *entry, int *fd)
