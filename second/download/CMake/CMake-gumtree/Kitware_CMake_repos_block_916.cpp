{
		if (errno == ENOTSUP || errno == ENOSYS)
			return (ARCHIVE_OK);
		archive_set_error(&a->archive, errno,
			"Couldn't list extended attributes");
		return (ARCHIVE_WARN);
	}