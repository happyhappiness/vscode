(uncompressed_size < 24 || header_size != 4 ||
	    log2_bs > 30 || log2_bs < 7)
		return;