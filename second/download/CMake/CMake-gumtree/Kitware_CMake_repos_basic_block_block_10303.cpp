(archive_be32dec(p + len) != checksum)
		goto corrupted;