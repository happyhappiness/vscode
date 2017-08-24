{
		ret = hfs_drive_compressor(a, buffer_to_write,
		    MAX_DECMPFS_BLOCK_SIZE - a->block_remaining_bytes);
		if (ret < 0)
			return (ret);
		a->block_remaining_bytes = MAX_DECMPFS_BLOCK_SIZE;
	}