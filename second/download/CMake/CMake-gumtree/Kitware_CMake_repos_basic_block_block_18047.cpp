{
	size_t in_start;
	lzma_ret ret;

	// Catch zero input buffer here, because in contrast to Index encoder
	// and decoder functions, applications call this function directly
	// instead of via lzma_code(), which does the buffer checking.
	if (*in_pos >= in_size)
		return LZMA_BUF_ERROR;

	// NOTE: This function has many similarities to index_encode() and
	// index_decode() functions found from index_encoder.c and
	// index_decoder.c. See the comments especially in index_encoder.c.
	in_start = *in_pos;
	ret = LZMA_OK;

	while (*in_pos < in_size)
	switch (index_hash->sequence) {
	case SEQ_BLOCK:
		// Check the Index Indicator is present.
		if (in[(*in_pos)++] != 0x00)
			return LZMA_DATA_ERROR;

		index_hash->sequence = SEQ_COUNT;
		break;

	case SEQ_COUNT: {
		ret = lzma_vli_decode(&index_hash->remaining,
				&index_hash->pos, in, in_pos, in_size);
		if (ret != LZMA_STREAM_END)
			goto out;

		// The count must match the count of the Blocks decoded.
		if (index_hash->remaining != index_hash->blocks.count)
			return LZMA_DATA_ERROR;

		ret = LZMA_OK;
		index_hash->pos = 0;

		// Handle the special case when there are no Blocks.
		index_hash->sequence = index_hash->remaining == 0
				? SEQ_PADDING_INIT : SEQ_UNPADDED;
		break;
	}

	case SEQ_UNPADDED:
	case SEQ_UNCOMPRESSED: {
		lzma_vli *size = index_hash->sequence == SEQ_UNPADDED
				? &index_hash->unpadded_size
				: &index_hash->uncompressed_size;

		ret = lzma_vli_decode(size, &index_hash->pos,
				in, in_pos, in_size);
		if (ret != LZMA_STREAM_END)
			goto out;

		ret = LZMA_OK;
		index_hash->pos = 0;

		if (index_hash->sequence == SEQ_UNPADDED) {
			if (index_hash->unpadded_size < UNPADDED_SIZE_MIN
					|| index_hash->unpadded_size
						> UNPADDED_SIZE_MAX)
				return LZMA_DATA_ERROR;

			index_hash->sequence = SEQ_UNCOMPRESSED;
		} else {
			// Update the hash.
			return_if_error(hash_append(&index_hash->records,
					index_hash->unpadded_size,
					index_hash->uncompressed_size));

			// Verify that we don't go over the known sizes. Note
			// that this validation is simpler than the one used
			// in lzma_index_hash_append(), because here we know
			// that values in index_hash->blocks are already
			// validated and we are fine as long as we don't
			// exceed them in index_hash->records.
			if (index_hash->blocks.blocks_size
					< index_hash->records.blocks_size
					|| index_hash->blocks.uncompressed_size
					< index_hash->records.uncompressed_size
					|| index_hash->blocks.index_list_size
					< index_hash->records.index_list_size)
				return LZMA_DATA_ERROR;

			// Check if this was the last Record.
			index_hash->sequence = --index_hash->remaining == 0
					? SEQ_PADDING_INIT : SEQ_UNPADDED;
		}

		break;
	}

	case SEQ_PADDING_INIT:
		index_hash->pos = (LZMA_VLI_C(4) - index_size_unpadded(
				index_hash->records.count,
				index_hash->records.index_list_size)) & 3;
		index_hash->sequence = SEQ_PADDING;

	// Fall through

	case SEQ_PADDING:
		if (index_hash->pos > 0) {
			--index_hash->pos;
			if (in[(*in_pos)++] != 0x00)
				return LZMA_DATA_ERROR;

			break;
		}

		// Compare the sizes.
		if (index_hash->blocks.blocks_size
				!= index_hash->records.blocks_size
				|| index_hash->blocks.uncompressed_size
				!= index_hash->records.uncompressed_size
				|| index_hash->blocks.index_list_size
				!= index_hash->records.index_list_size)
			return LZMA_DATA_ERROR;

		// Finish the hashes and compare them.
		lzma_check_finish(&index_hash->blocks.check, LZMA_CHECK_BEST);
		lzma_check_finish(&index_hash->records.check, LZMA_CHECK_BEST);
		if (memcmp(index_hash->blocks.check.buffer.u8,
				index_hash->records.check.buffer.u8,
				lzma_check_size(LZMA_CHECK_BEST)) != 0)
			return LZMA_DATA_ERROR;

		// Finish the CRC32 calculation.
		index_hash->crc32 = lzma_crc32(in + in_start,
				*in_pos - in_start, index_hash->crc32);

		index_hash->sequence = SEQ_CRC32;

	// Fall through

	case SEQ_CRC32:
		do {
			if (*in_pos == in_size)
				return LZMA_OK;

			if (((index_hash->crc32 >> (index_hash->pos * 8))
					& 0xFF) != in[(*in_pos)++])
				return LZMA_DATA_ERROR;

		} while (++index_hash->pos < 4);

		return LZMA_STREAM_END;

	default:
		assert(0);
		return LZMA_PROG_ERROR;
	}

out:
	// Update the CRC32,
	index_hash->crc32 = lzma_crc32(in + in_start,
			*in_pos - in_start, index_hash->crc32);

	return ret;
}