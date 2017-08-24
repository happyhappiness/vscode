(((index_hash->crc32 >> (index_hash->pos * 8))
					& 0xFF) != in[(*in_pos)++])
				return LZMA_DATA_ERROR;