{
		r = write_file_contents(a, offset,
		    blocks << LOGICAL_BLOCK_BITS);
		if (r < 0)
			return (r);
	}