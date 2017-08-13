{
		archive_set_error(&a->archive, errno,
		    "Cannot restore xattr:%s", DECMPFS_XATTR_NAME);
		compression_type = archive_le32dec(
		    &a->decmpfs_header_p[DECMPFS_COMPRESSION_TYPE]);
		if (compression_type == CMP_RESOURCE_FORK)
			fremovexattr(a->fd, XATTR_RESOURCEFORK_NAME,
			    XATTR_SHOWCOMPRESSION);
		return (ARCHIVE_WARN);
	}