{
	bool is_bt;
	uint32_t new_count;
	uint32_t reserve;
	uint32_t old_size;
	uint32_t hash_bytes;
	uint32_t hs;
	uint32_t old_count;

	// For now, the dictionary size is limited to 1.5 GiB. This may grow
	// in the future if needed, but it needs a little more work than just
	// changing this check.
	if (lz_options->dict_size < LZMA_DICT_SIZE_MIN
			|| lz_options->dict_size
				> (UINT32_C(1) << 30) + (UINT32_C(1) << 29)
			|| lz_options->nice_len > lz_options->match_len_max)
		return true;

	mf->keep_size_before = lz_options->before_size + lz_options->dict_size;

	mf->keep_size_after = lz_options->after_size
			+ lz_options->match_len_max;

	// To avoid constant memmove()s, allocate some extra space. Since
	// memmove()s become more expensive when the size of the buffer
	// increases, we reserve more space when a large dictionary is
	// used to make the memmove() calls rarer.
	//
	// This works with dictionaries up to about 3 GiB. If bigger
	// dictionary is wanted, some extra work is needed:
	//   - Several variables in lzma_mf have to be changed from uint32_t
	//     to size_t.
	//   - Memory usage calculation needs something too, e.g. use uint64_t
	//     for mf->size.
	reserve = lz_options->dict_size / 2;
	if (reserve > (UINT32_C(1) << 30))
		reserve /= 2;

	reserve += (lz_options->before_size + lz_options->match_len_max
			+ lz_options->after_size) / 2 + (UINT32_C(1) << 19);

	old_size = mf->size;
	mf->size = mf->keep_size_before + reserve + mf->keep_size_after;

	// Deallocate the old history buffer if it exists but has different
	// size than what is needed now.
	if (mf->buffer != NULL && old_size != mf->size) {
		lzma_free(mf->buffer, allocator);
		mf->buffer = NULL;
	}

	// Match finder options
	mf->match_len_max = lz_options->match_len_max;
	mf->nice_len = lz_options->nice_len;

	// cyclic_size has to stay smaller than 2 Gi. Note that this doesn't
	// mean limiting dictionary size to less than 2 GiB. With a match
	// finder that uses multibyte resolution (hashes start at e.g. every
	// fourth byte), cyclic_size would stay below 2 Gi even when
	// dictionary size is greater than 2 GiB.
	//
	// It would be possible to allow cyclic_size >= 2 Gi, but then we
	// would need to be careful to use 64-bit types in various places
	// (size_t could do since we would need bigger than 32-bit address
	// space anyway). It would also require either zeroing a multigigabyte
	// buffer at initialization (waste of time and RAM) or allow
	// normalization in lz_encoder_mf.c to access uninitialized
	// memory to keep the code simpler. The current way is simple and
	// still allows pretty big dictionaries, so I don't expect these
	// limits to change.
	mf->cyclic_size = lz_options->dict_size + 1;

	// Validate the match finder ID and setup the function pointers.
	switch (lz_options->match_finder) {
#ifdef HAVE_MF_HC3
	case LZMA_MF_HC3:
		mf->find = &lzma_mf_hc3_find;
		mf->skip = &lzma_mf_hc3_skip;
		break;
#endif
#ifdef HAVE_MF_HC4
	case LZMA_MF_HC4:
		mf->find = &lzma_mf_hc4_find;
		mf->skip = &lzma_mf_hc4_skip;
		break;
#endif
#ifdef HAVE_MF_BT2
	case LZMA_MF_BT2:
		mf->find = &lzma_mf_bt2_find;
		mf->skip = &lzma_mf_bt2_skip;
		break;
#endif
#ifdef HAVE_MF_BT3
	case LZMA_MF_BT3:
		mf->find = &lzma_mf_bt3_find;
		mf->skip = &lzma_mf_bt3_skip;
		break;
#endif
#ifdef HAVE_MF_BT4
	case LZMA_MF_BT4:
		mf->find = &lzma_mf_bt4_find;
		mf->skip = &lzma_mf_bt4_skip;
		break;
#endif

	default:
		return true;
	}

	// Calculate the sizes of mf->hash and mf->son and check that
	// nice_len is big enough for the selected match finder.
	hash_bytes = lz_options->match_finder & 0x0F;
	if (hash_bytes > mf->nice_len)
		return true;

	is_bt = (lz_options->match_finder & 0x10) != 0;

	if (hash_bytes == 2) {
		hs = 0xFFFF;
	} else {
		// Round dictionary size up to the next 2^n - 1 so it can
		// be used as a hash mask.
		hs = lz_options->dict_size - 1;
		hs |= hs >> 1;
		hs |= hs >> 2;
		hs |= hs >> 4;
		hs |= hs >> 8;
		hs >>= 1;
		hs |= 0xFFFF;

		if (hs > (UINT32_C(1) << 24)) {
			if (hash_bytes == 3)
				hs = (UINT32_C(1) << 24) - 1;
			else
				hs >>= 1;
		}
	}

	mf->hash_mask = hs;

	++hs;
	if (hash_bytes > 2)
		hs += HASH_2_SIZE;
	if (hash_bytes > 3)
		hs += HASH_3_SIZE;
/*
	No match finder uses this at the moment.
	if (mf->hash_bytes > 4)
		hs += HASH_4_SIZE;
*/

	// If the above code calculating hs is modified, make sure that
	// this assertion stays valid (UINT32_MAX / 5 is not strictly the
	// exact limit). If it doesn't, you need to calculate that
	// hash_size_sum + sons_count cannot overflow.
	assert(hs < UINT32_MAX / 5);

	old_count = mf->hash_size_sum + mf->sons_count;
	mf->hash_size_sum = hs;
	mf->sons_count = mf->cyclic_size;
	if (is_bt)
		mf->sons_count *= 2;

	new_count = mf->hash_size_sum + mf->sons_count;

	// Deallocate the old hash array if it exists and has different size
	// than what is needed now.
	if (old_count != new_count) {
		lzma_free(mf->hash, allocator);
		mf->hash = NULL;
	}

	// Maximum number of match finder cycles
	mf->depth = lz_options->depth;
	if (mf->depth == 0) {
		if (is_bt)
			mf->depth = 16 + mf->nice_len / 2;
		else
			mf->depth = 4 + mf->nice_len / 4;
	}

	return false;
}