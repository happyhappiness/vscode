{
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