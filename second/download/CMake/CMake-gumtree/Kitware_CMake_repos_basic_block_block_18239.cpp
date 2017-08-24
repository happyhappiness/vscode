{
	size_t i, j;

	if (!is_options_valid(options))
		return LZMA_OPTIONS_ERROR;

	coder->pos_mask = (1U << options->pb) - 1;
	coder->literal_context_bits = options->lc;
	coder->literal_pos_mask = (1U << options->lp) - 1;

	// Range coder
	rc_reset(&coder->rc);

	// State
	coder->state = STATE_LIT_LIT;
	for (i = 0; i < REP_DISTANCES; ++i)
		coder->reps[i] = 0;

	literal_init(coder->literal, options->lc, options->lp);

	// Bit encoders
	for (i = 0; i < STATES; ++i) {
		for (j = 0; j <= coder->pos_mask; ++j) {
			bit_reset(coder->is_match[i][j]);
			bit_reset(coder->is_rep0_long[i][j]);
		}

		bit_reset(coder->is_rep[i]);
		bit_reset(coder->is_rep0[i]);
		bit_reset(coder->is_rep1[i]);
		bit_reset(coder->is_rep2[i]);
	}

	for (i = 0; i < FULL_DISTANCES - END_POS_MODEL_INDEX; ++i)
		bit_reset(coder->pos_special[i]);

	// Bit tree encoders
	for (i = 0; i < LEN_TO_POS_STATES; ++i)
		bittree_reset(coder->pos_slot[i], POS_SLOT_BITS);

	bittree_reset(coder->pos_align, ALIGN_BITS);

	// Length encoders
	length_encoder_reset(&coder->match_len_encoder,
			1U << options->pb, coder->fast_mode);

	length_encoder_reset(&coder->rep_len_encoder,
			1U << options->pb, coder->fast_mode);

	// Price counts are incremented every time appropriate probabilities
	// are changed. price counts are set to zero when the price tables
	// are updated, which is done when the appropriate price counts have
	// big enough value, and lzma_mf.read_ahead == 0 which happens at
	// least every OPTS (a few thousand) possible price count increments.
	//
	// By resetting price counts to UINT32_MAX / 2, we make sure that the
	// price tables will be initialized before they will be used (since
	// the value is definitely big enough), and that it is OK to increment
	// price counts without risk of integer overflow (since UINT32_MAX / 2
	// is small enough). The current code doesn't increment price counts
	// before initializing price tables, but it maybe done in future if
	// we add support for saving the state between LZMA2 chunks.
	coder->match_price_count = UINT32_MAX / 2;
	coder->align_price_count = UINT32_MAX / 2;

	coder->opts_end_index = 0;
	coder->opts_current_index = 0;

	return LZMA_OK;
}