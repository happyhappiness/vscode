ret = lzma_index_append(i, allocator,
					lzma_block_unpadded_size(&block),
					block.uncompressed_size)