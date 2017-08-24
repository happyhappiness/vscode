{
	lzma_options_lzma *opt;

	// New options can be set only when there is no incomplete chunk.
	// This is the case at the beginning of the raw stream and right
	// after LZMA_SYNC_FLUSH.
	if (filter->options == NULL || coder->sequence != SEQ_INIT)
		return LZMA_PROG_ERROR;

	// Look if there are new options. At least for now,
	// only lc/lp/pb can be changed.
	opt = filter->options;
	if (coder->opt_cur.lc != opt->lc || coder->opt_cur.lp != opt->lp
			|| coder->opt_cur.pb != opt->pb) {
		// Validate the options.
		if (opt->lc > LZMA_LCLP_MAX || opt->lp > LZMA_LCLP_MAX
				|| opt->lc + opt->lp > LZMA_LCLP_MAX
				|| opt->pb > LZMA_PB_MAX)
			return LZMA_OPTIONS_ERROR;

		// The new options will be used when the encoder starts
		// a new LZMA2 chunk.
		coder->opt_cur.lc = opt->lc;
		coder->opt_cur.lp = opt->lp;
		coder->opt_cur.pb = opt->pb;
		coder->need_properties = true;
		coder->need_state_reset = true;
	}

	return LZMA_OK;
}