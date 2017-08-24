{
		size_t new_block_size = 64 * 1024;
		while (new_block_size < mine->block_size
		    && new_block_size < 64 * 1024 * 1024)
			new_block_size *= 2;
		mine->block_size = new_block_size;
	}