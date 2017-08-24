{
		int r2;
#ifdef HAVE_DARWIN_ACL
		/*
		 * On Mac OS, platform ACLs are stored also in mac_metadata by
		 * the operating system. If mac_metadata is present it takes
		 * precedence and we skip extracting libarchive NFSv4 ACLs
		 */
		const void *metadata;
		size_t metadata_size;
		metadata = archive_entry_mac_metadata(a->entry, &metadata_size);
		if ((a->todo & TODO_MAC_METADATA) == 0 ||
		    metadata == NULL || metadata_size == 0) {
#endif
		r2 = archive_write_disk_set_acls(&a->archive, a->fd,
		    archive_entry_pathname(a->entry),
		    archive_entry_acl(a->entry));
		if (r2 < ret) ret = r2;
#ifdef HAVE_DARWIN_ACL
		}
#endif
	}