{
		unsigned int chsum = __archive_xxhash.XXH32(
			read_buf + 4, (int)compressed_size, 0);
		unsigned int chsum_block =
		    archive_le32dec(read_buf + 4 + compressed_size);
		if (chsum != chsum_block)
			goto malformed_error;
	}