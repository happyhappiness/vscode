{
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