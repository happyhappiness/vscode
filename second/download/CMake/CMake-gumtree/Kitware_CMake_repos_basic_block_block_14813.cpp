{
		archive_le32enc(&a->decmpfs_header_p[DECMPFS_COMPRESSION_TYPE],
		    CMP_XATTR);
		memcpy(a->decmpfs_header_p + DECMPFS_HEADER_SIZE,
		    buffer_compressed, bytes_compressed);
		a->decmpfs_attr_size += bytes_compressed;
		a->compressed_buffer_remaining = a->compressed_buffer_size;
		/*
		 * Finish HFS+ Compression.
		 * - Write the decmpfs xattr.
		 * - Set the UF_COMPRESSED file flag.
		 */
		ret = hfs_write_decmpfs(a);
		if (ret == ARCHIVE_OK)
			ret = hfs_set_compressed_fflag(a);
		return (ret);
	}