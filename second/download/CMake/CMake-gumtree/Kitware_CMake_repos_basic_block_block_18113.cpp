{
		// Match finder may update coder->pending and expects it to
		// start from zero, so use a temporary variable.
		const size_t pending = coder->mf.pending;
		coder->mf.pending = 0;

		// Rewind read_pos so that the match finder can hash
		// the pending bytes.
		assert(coder->mf.read_pos >= pending);
		coder->mf.read_pos -= pending;

		// Call the skip function directly instead of using
		// mf_skip(), since we don't want to touch mf->read_ahead.
		coder->mf.skip(&coder->mf, pending);
	}