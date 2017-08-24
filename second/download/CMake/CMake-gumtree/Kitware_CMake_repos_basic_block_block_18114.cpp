{
		// This needs to be done conditionally, because if we got
		// only little new input, there may be too little input
		// to do any encoding yet.
		coder->mf.read_limit = coder->mf.write_pos
				- coder->mf.keep_size_after;
	}