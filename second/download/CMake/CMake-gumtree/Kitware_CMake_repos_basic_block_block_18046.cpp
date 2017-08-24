(index_hash->blocks.blocks_size
					< index_hash->records.blocks_size
					|| index_hash->blocks.uncompressed_size
					< index_hash->records.uncompressed_size
					|| index_hash->blocks.index_list_size
					< index_hash->records.index_list_size)
				return LZMA_DATA_ERROR;