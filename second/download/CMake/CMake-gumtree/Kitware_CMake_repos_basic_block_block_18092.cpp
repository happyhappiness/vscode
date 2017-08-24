(crc != unaligned_read32le(in))
		return LZMA_DATA_ERROR;