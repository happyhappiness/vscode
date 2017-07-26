	case 'S':
		/* We support some keys used by the "star" archiver */
		if (strcmp(key, "SCHILY.acl.access") == 0) {
			r = pax_attribute_acl(a, tar, entry, value,
			    ARCHIVE_ENTRY_ACL_TYPE_ACCESS);
			if (r == ARCHIVE_FATAL)
				return (r);
		} else if (strcmp(key, "SCHILY.acl.default") == 0) {
			r = pax_attribute_acl(a, tar, entry, value,
			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT);
			if (r == ARCHIVE_FATAL)
				return (r);
		} else if (strcmp(key, "SCHILY.acl.ace") == 0) {
			r = pax_attribute_acl(a, tar, entry, value,
			    ARCHIVE_ENTRY_ACL_TYPE_NFS4);
			if (r == ARCHIVE_FATAL)
				return (r);
		} else if (strcmp(key, "SCHILY.devmajor") == 0) {
			archive_entry_set_rdevmajor(entry,
			    (dev_t)tar_atol10(value, strlen(value)));
