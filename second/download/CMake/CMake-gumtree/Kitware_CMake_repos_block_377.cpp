{
		if (errno == ENOENT)
			/* There are not any ACLs. */
			return (ret);
		archive_set_error(&a->archive, errno,
		    "Failed to get metadata(acl)");
		ret = ARCHIVE_WARN;
		goto exit_acl;
	}