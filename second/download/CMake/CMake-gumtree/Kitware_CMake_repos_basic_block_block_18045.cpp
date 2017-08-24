{
			if (index_hash->unpadded_size < UNPADDED_SIZE_MIN
					|| index_hash->unpadded_size
						> UNPADDED_SIZE_MAX)
				return LZMA_DATA_ERROR;

			index_hash->sequence = SEQ_UNCOMPRESSED;
		}