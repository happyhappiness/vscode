{
	assert(mf_position(mf) == 0);

	if (mf->read_pos == mf->read_limit) {
		if (mf->action == LZMA_RUN)
			return false; // We cannot do anything.

		// We are finishing (we cannot get here when flushing).
		assert(mf->write_pos == mf->read_pos);
		assert(mf->action == LZMA_FINISH);
	} else {
		// Do the actual initialization. The first LZMA symbol must
		// always be a literal.
		mf_skip(mf, 1);
		mf->read_ahead = 0;
		rc_bit(&coder->rc, &coder->is_match[0][0], 0);
		rc_bittree(&coder->rc, coder->literal[0], 8, mf->buffer[0]);
	}

	// Initialization is done (except if empty file).
	coder->is_initialized = true;

	return true;
}