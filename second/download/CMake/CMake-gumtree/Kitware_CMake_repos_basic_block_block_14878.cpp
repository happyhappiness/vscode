{
		char null_d[1024];
		ssize_t r;

		if (a->file_remaining_bytes)
			memset(null_d, 0, sizeof(null_d));
		while (a->file_remaining_bytes) {
			if (a->file_remaining_bytes > sizeof(null_d))
				r = hfs_write_data_block(
				    a, null_d, sizeof(null_d));
			else
				r = hfs_write_data_block(
				    a, null_d, a->file_remaining_bytes);
			if (r < 0)
				return ((int)r);
		}
#endif
	}