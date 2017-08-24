{
		size_t rsrc_size;
		int64_t bk;

		/* Append the resource footer. */
		rsrc_size = hfs_set_resource_fork_footer(
		    a->compressed_buffer + bytes_used,
		    a->compressed_buffer_remaining);
		ret = hfs_write_compressed_data(a, bytes_used + rsrc_size);
		a->compressed_buffer_remaining = a->compressed_buffer_size;

		/* If the compressed size is not enough smaller than
		 * the uncompressed size. cancel HFS+ compression.
		 * TODO: study a behavior of ditto utility and improve
		 * the condition to fall back into no HFS+ compression. */
		bk = HFS_BLOCKS(a->compressed_rsrc_position);
		bk += bk >> 7;
		if (bk > HFS_BLOCKS(a->filesize))
			return hfs_decompress(a);
		/*
		 * Write the resourcefork header.
		 */
		if (ret == ARCHIVE_OK)
			ret = hfs_write_resource_fork_header(a);
		/*
		 * Finish HFS+ Compression.
		 * - Write the decmpfs xattr.
		 * - Set the UF_COMPRESSED file flag.
		 */
		if (ret == ARCHIVE_OK)
			ret = hfs_write_decmpfs(a);
		if (ret == ARCHIVE_OK)
			ret = hfs_set_compressed_fflag(a);
	}